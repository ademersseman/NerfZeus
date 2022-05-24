#include <LiquidCrystal.h>
#include <FastLED.h>

#define NUM_LEDS 16
#define LED_DATA_PIN 11
#define LED_POWER_PIN 10
#define MOTOR_TRIGGER_PIN 4
#define MOTOR_POWER_PIN 6
#define MAIN_TRIGGER_PIN 13
#define SOLENOID_POWER_PIN 12

LiquidCrystal lcd(8, 7, 9, 3, 2, 1);

byte ammo = 12;

CRGB leds[16];

void setup() {

  lcd.begin(16, 2);
  lcd.print("Welcome, Soldier");
  lcd.setCursor(15, 1);
  lcd.print("V");

  lcd.setCursor(0, 1);
  lcd.print(ammo);

  pinMode(MOTOR_POWER_PIN, OUTPUT);
  pinMode(LED_POWER_PIN, OUTPUT);
  pinMode(MOTOR_TRIGGER_PIN, INPUT);
  pinMode(MAIN_TRIGGER_PIN, INPUT);
  pinMode(LCD_PWM_PIN, OUTPUT);
  pinMode(SOLENOID_POWER_PIN, OUTPUT);

  FastLED.setBrightness(30);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  for (int i = 2; i < 14; i++) {
      leds[i] = CRGB::Blue;
  }
  FastLED.show();

  digitalWrite(LED_POWER_PIN, HIGH);
}

void loop() {
  while (digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {
    digitalWrite(SOLENOID_POWER_PIN, HIGH);//enables solenoid
    digitalWrite(MOTOR_POWER_PIN, HIGH);//enables motor
    if (digitalRead(MAIN_TRIGGER_PIN) == HIGH) {
      shoot();
    }
  }
  digitalWrite(MOTOR_POWER_PIN, LOW);
  updateVoltmeter();
}

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
  leds[13 - ammo] = CRGB::Black;
  if (ammo == 0) {
    ammo = 12;
    leds[0] = CRGB::Blue;
    for (int i = 2; i < 14; i++) {
      leds[i] = CRGB::Blue;
    }
    for (int i = 2; i < 8; i++) {
      leds[i].fadeLightBy(235);
    }
  }
  FastLED.show();
}

void shoot() {
  ammo--;
  decrimentStripLength();
  updateAmmoCounter();

  delay(42);//time to shoot one ball
      
  digitalWrite(SOLENOID_POWER_PIN, LOW);
      
  delay(100);//delay between rounds
}
