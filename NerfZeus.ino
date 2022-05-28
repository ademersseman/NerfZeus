#include <LiquidCrystal.h>
#include <FastLED.h>

#define NUM_LEDS 16
#define LED_DATA_PIN 11
#define LED_POWER_PIN 10
#define MOTOR_TRIGGER_PIN 4
#define MOTOR_POWER_PIN 6
#define MAIN_TRIGGER_PIN 13
#define SOLENOID_POWER_PIN 12
#define IR_SENSOR_PIN A6

LiquidCrystal lcd(8, 7, 9, 3, 2, 1);

byte motorFactor = 250;//motor speed value
byte ammo;//ammo variable
unsigned int shotDelay = 500;//delay between shots in milliseconds

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(MOTOR_POWER_PIN, OUTPUT);
  pinMode(LED_POWER_PIN, OUTPUT);
  pinMode(MOTOR_TRIGGER_PIN, INPUT);
  pinMode(MAIN_TRIGGER_PIN, INPUT);
  pinMode(SOLENOID_POWER_PIN, OUTPUT);

  FastLED.setBrightness(30);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
  initialize();
}



void loop() {
  while (digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {//user repressed motor rev switch
    digitalWrite(SOLENOID_POWER_PIN, HIGH);//enables solenoid
    analogWrite(MOTOR_POWER_PIN, motorFactor);//enables motor
    if (digitalRead(MAIN_TRIGGER_PIN) == HIGH) {
      shoot();
      delay(shotDelay);//delay between shots
    }
  }
  digitalWrite(MOTOR_POWER_PIN, LOW);
  updateVoltmeter();
  delay(1);
}

//updates voltmeter and displays LCD
void updateVoltmeter() {
  int analog_value = analogRead(A7);
  float temp = (analog_value * 5.0) / 1024.0;
  float input_voltage = (float)temp / (51.0 / 151.0);
  if (input_voltage < 0.5)
  {
    input_voltage = 0.0;
  }
  lcd.setCursor(11, 1);
  lcd.print(input_voltage);
}

//updates ammo variable value
void updateAmmoCounter() {
  if (ammo < 10) {
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(1, 1);
  } else {
    lcd.setCursor(0, 1);
  }
  lcd.print(ammo);
}

//updates strip for new ammo value
void decrimentStripLength() {
  leds[12 - ammo] = CRGB::Black;
  leds[13 - ammo] = CRGB::Black;
  FastLED.show();
}

//resets ammo variable, updates LCD, and LED strip with this new value
void reload() {
  ammo = 12;
  updateAmmoCounter();
  
  for (int i = 2; i < 14; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 2; i < 8; i++) {//dims first LEDs in series
    leds[i].fadeLightBy(235);
  }
  FastLED.show();
}

//interprets a trigger pull
void shoot() {
  unsigned int timer = 0; 
  noInterrupts();//dissables interrupts
  while (analogRead(IR_SENSOR_PIN) != 0) {//waiting for IR receiver to detect a shot to passing through the barrel
    timer++;//include speed of update here
    if (timer > 2000 && digitalRead(MAIN_TRIGGER_PIN) == LOW) {//will reload, assumed user has ran out of ammo
      ammo = 2;
      break;
    } else if (timer > 40000 && digitalRead(MAIN_TRIGGER_PIN) == HIGH) {//will enter programming mode
      ammo = 2;
      enterSettings();
      break;
    }
  }
  digitalWrite(SOLENOID_POWER_PIN, LOW);//disables power to the solenoid
  interrupts();//enables interrupts

  ammo -= 2;//subtracts two from ammo total, IR sensor is too slow and will allow two balls beforing tripping
  if (ammo <= 0) {
    reload();
  } else {
    updateAmmoCounter();
    decrimentStripLength();
  }
}

//flashes red x amount of times
void flashRed(int x) {
  if (x == 0) {
    return;
  }
  ledStripOff();
  delay(100);
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB::Red;
  }
  for (int i = 0; i < 8; i++) {//dims first LEDs in series
    leds[i].fadeLightBy(200);
  }
  FastLED.show();
    
  flashRed(x - 1);
}

//turns off the led strip
void ledStripOff() {
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

//resets LED strip and LCD, calls reload()
void initialize() {
  lcd.clear();
  ledStripOff();
  digitalWrite(LED_POWER_PIN, HIGH);
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Welcome, Alan");
  lcd.setCursor(15, 1);
  lcd.print("V");
  leds[0] = CRGB::Blue;
  reload();
}

//loop for user changing motor speed and delay between shots 
void interpretPress() {
  unsigned int timer = 0;
  boolean state = true;
  while(timer < 4000) {
    while(digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {
      if (timer < 65535) {//unsigned int max value
        timer++;
      }
      delay(1);
    }
    if (timer > 1000) {//swap user changes to other values
      state = !state;
    } else if (timer > 100) {
      if (state) {//increment shot delay
        if (shotDelay == 1000) {//max shot delay
          lcd.setCursor(6, 1);
          lcd.print("    ");
          shotDelay = 0;//reset to zero shot delay
        } else {
          shotDelay += 100;
        }
        lcd.setCursor(6, 1);
        lcd.print(shotDelay);//print new value to LCD
      } else {//increment motor speed
        if (motorFactor == 250) {//max motorFactor
          motorFactor = 100;//reset to minimum motor speed
        } else {
          motorFactor += 15;
        }
        lcd.setCursor(6, 0);
        lcd.print(motorFactor);//print new value to LCD
      }
    }
    timer = 0;//reset timer
  }
}

//initializes
void enterSettings() {
  digitalWrite(SOLENOID_POWER_PIN, LOW);//disabling all blaster controls
  analogWrite(MOTOR_POWER_PIN, LOW);
  digitalWrite(LED_POWER_PIN, LOW);
  flashRed(5);//flash LED strip red
  lcd.clear();//prints to LCD user interface for changing shot delay and motor speed
  lcd.setCursor(0, 0);
  lcd.print("Motor:");
  lcd.setCursor(6, 0);
  lcd.print(motorFactor);
  lcd.setCursor(0, 1);
  lcd.print("Delay:");
  lcd.setCursor(6, 1);
  lcd.print(shotDelay);

  interpretPress();//enter loop for user input
  initialize();//reset blaster with new user defined settings
}
