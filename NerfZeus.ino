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

byte motorFactor = 250;
byte ammo;
unsigned int shotDelay = 500;

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(MOTOR_POWER_PIN, OUTPUT);
  pinMode(LED_POWER_PIN, OUTPUT);
  pinMode(MOTOR_TRIGGER_PIN, INPUT);
  pinMode(MAIN_TRIGGER_PIN, INPUT);
  pinMode(SOLENOID_POWER_PIN, OUTPUT);

  FastLED.setBrightness(30);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  initialize();
}



void loop() {
  while (digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {
    digitalWrite(SOLENOID_POWER_PIN, HIGH);//enables solenoid
    analogWrite(MOTOR_POWER_PIN, motorFactor);//enables motor
    if (digitalRead(MAIN_TRIGGER_PIN) == HIGH) {
      shoot();
      delay(shotDelay);
    }
  }
  digitalWrite(MOTOR_POWER_PIN, LOW);
  updateVoltmeter();
  delay(1);
}

//update voltmeter
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

void decrimentStripLength() {
  leds[12 - ammo] = CRGB::Black;
  leds[13 - ammo] = CRGB::Black;
  FastLED.show();
}

void reload() {
  ammo = 12;
  updateAmmoCounter();
  
  leds[0] = CRGB::Blue;
  for (int i = 2; i < 14; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 2; i < 8; i++) {
    leds[i].fadeLightBy(235);
  }
  FastLED.show();
}

void shoot() {
  unsigned int timer = 0; 
  noInterrupts();
  while (analogRead(IR_SENSOR_PIN) != 0) {
    timer++;
    if (timer > 2000 && digitalRead(MAIN_TRIGGER_PIN) == LOW) {
      ammo = 2;
      break;
    } else if (timer > 50000 && digitalRead(MAIN_TRIGGER_PIN) == HIGH) {
      ammo = 2;
      enterSettings();
      break;
    }
  }
  digitalWrite(SOLENOID_POWER_PIN, LOW);
  interrupts();

  ammo -= 2;
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
  } else {
    ledStripOff();
    delay(100);
    for (int i = 0; i < 16; i++) {
      leds[i] = CRGB::Red;
    }
    for (int i = 0; i < 8; i++) {
      leds[i].fadeLightBy(200);
    }
    FastLED.show();
    
    flashRed(x - 1);
  }
}

//turns off the led strip
void ledStripOff() {
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void initialize() {
  lcd.clear();
  ledStripOff();
  digitalWrite(LED_POWER_PIN, HIGH);
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Welcome, Soldier");
  lcd.setCursor(15, 1);
  lcd.print("V");
  reload();
}

boolean interpretPress() {
  boolean flag = true;
  boolean turn = true;
  while(flag) {
    unsigned int timer = 0;
    while(digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {
      timer++;
      if (timer > 4000) {
        flag = false;
        break;
      }
      delay(1);
    }
    if (timer > 1000) {
      if (turn) {
        turn = false;
      } else {
        turn = true;
      }
    } else if (timer > 100) {
      if (turn) {
        if (shotDelay == 1000) {
          lcd.setCursor(6, 1);
          lcd.print("    ");
          shotDelay = 0;
        } else {
          shotDelay += 100;
        }
        lcd.setCursor(6, 1);
        lcd.print(shotDelay);
      } else {
        if (motorFactor == 250) {
          motorFactor = 100;
        } else {
          motorFactor += 15;
        }
        lcd.setCursor(6, 0);
        lcd.print(motorFactor);
      }
    }
  }
}
void enterSettings() {
  digitalWrite(SOLENOID_POWER_PIN, LOW);
  analogWrite(MOTOR_POWER_PIN, LOW);
  digitalWrite(LED_POWER_PIN, LOW);
  flashRed(5);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor:");
  lcd.setCursor(6, 0);
  lcd.print(motorFactor);
  lcd.setCursor(0, 1);
  lcd.print("Delay:");
  lcd.setCursor(6, 1);
  lcd.print(shotDelay);

  interpretPress();
  initialize();
}
