#include <LiquidCrystal.h>
#include <FastLED.h>

#define NUM_LEDS 16
#define LED_DATA_PIN 11
#define LED_POWER_PIN 10
#define MOTOR_TRIGGER_PIN 4//detects user pressing motor trigger
#define MOTOR_POWER_PIN 6//controls power sent to the motor
#define MAIN_TRIGGER_PIN 13//detects user pressing main trigger pin
#define SOLENOID_POWER_PIN 12//controls whether the solenoid is triggerable
#define IR_SENSOR_PIN A6
#define VOLTMETER_PIN A7

LiquidCrystal lcd(8, 7, 9, 3, 2, 1);

byte motorFactor = 250;//motor speed value
byte ammo;//ammo count
int shotDelay = 500;//delay between shots in milliseconds

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
  reload();
}



void loop() {
  while (digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {//user pressed motor rev switch
    digitalWrite(SOLENOID_POWER_PIN, HIGH);//activates solenoid
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

//updates voltmeter and displays to LCD
void updateVoltmeter() {
  float input_voltage = (analogRead(VOLTMETER_PIN) * 5.0) / 1024.0;//converts the analog read output into a ratio out of 5V(analogRead(VOLTMETER_PIN) = 1024 when 5V)
  input_voltage = input_voltage / (51.0 / 151.0);//voltage divider calculation max ~ 15V
  lcd.setCursor(11, 1);
  lcd.print(input_voltage);
}

//writes ammo variable value to LCD display
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
  
  //fills LED strip
  for (int i = 2; i < 14; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 2; i < 8; i++) {//dims first LEDs in series
    leds[i].fadeLightBy(235);
  }
  FastLED.show();
}

//interprets a main trigger pull
void shoot() {
  unsigned long start = millis(); 
  while (analogRead(IR_SENSOR_PIN) != 0) {//while IR sensor detects no ball fired
    if (millis() - start > 200 && digitalRead(MAIN_TRIGGER_PIN) == LOW) {//if no balls are fired withing 200ms and the user releases the main trigger
      ammo = 2;
      break;
    } else if (millis() - start > 2000 && digitalRead(MAIN_TRIGGER_PIN) == HIGH) {//if the user pulls the trigger down on empty magazine for 2000ms = 2s
      ammo = 2;
      enterSettings();
      break;
    }
  }
  digitalWrite(SOLENOID_POWER_PIN, LOW);//disables power to the solenoid

  ammo -= 2;//subtracts two from ammo total, IR sensor is too slow and will allow two balls beforing tripping
  if (ammo <= 0) {
    reload();
  } else {
    updateAmmoCounter();
    decrimentStripLength();
  }
}

//flashes red x amount of times
void flashRed(int repeat) {
  for (repeat; repeat > 0; repeat--){
    ledStripOff();
    delay(100);//will be black for 100ms
    for (int i = 0; i < 16; i++) {
      leds[i] = CRGB::Red;
    }
    for (int i = 0; i < 8; i++) {//dims first LEDs in series
      leds[i].fadeLightBy(200);
    }
    FastLED.show();
    delay(10);//will be red for 10ms
  }
}

//turns off the led strip
void ledStripOff() {
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

//resets LED strip, LCD, and lightning bolt LED
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
}


//enters the settings page
void enterSettings() {
  //disabling all blaster controls
  digitalWrite(SOLENOID_POWER_PIN, LOW);
  analogWrite(MOTOR_POWER_PIN, LOW);
  digitalWrite(LED_POWER_PIN, LOW);
  flashRed(5);
  lcd.clear();
  //prints to LCD user interface for changing shot delay and motor speed
  lcd.setCursor(0, 0);
  lcd.print("Motor:");
  lcd.setCursor(6, 0);
  lcd.print(motorFactor);
  lcd.setCursor(0, 1);
  lcd.print("Delay:");
  lcd.setCursor(6, 1);
  lcd.print(shotDelay);

//loop for user changing motor speed and delay between shots exits when user holds button for 4 seconds
  unsigned long start = millis();//recording of when user presses button
  boolean state = true;//true when user is changing delay between shots, false when changing motor speed
  while(millis() - start < 4000) {
    start = millis();//reset timer
    while(digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {//let clock run while user presses the motor trigger
      delay(1);
    }
    if (millis() - start > 1000) {//swap user changes
      state = !state;//switch state
    } else if (millis() - start > 100) {
      if (state) {//increment shot delay
        if (shotDelay == 1000) {//max shot delay
          lcd.setCursor(6, 1);
          lcd.print("    ");//wipe screen, otherwise the last zero will not be overwritten when printing 100
          shotDelay = 0;//reset to zero shot delay
        } else {
          shotDelay += 100;//increments of 100ms
        }
        //write change to LCD display
        lcd.setCursor(6, 1);
        lcd.print(shotDelay);
      } else {//increment motor speed
        if (motorFactor == 250) {//max motorFactor
          motorFactor = 100;//reset to minimum motor speed
        } else {
          motorFactor += 15;//increments byte by 15
        }
        //write change to LCD display
        lcd.setCursor(6, 0);
        lcd.print(motorFactor);
      }
    }
  }
  initialize();//reset blaster with new user defined settings
}
