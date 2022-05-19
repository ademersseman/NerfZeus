#include <LiquidCrystal.h>
#include <FastLED.h>

#define NUM_LEDS 16
#define LED_DATA_PIN 11
#define LED_POWER_PIN 10
#define LCD_PWM_PIN 5
#define MOTOR_TRIGGER_PIN 4
#define MOTOR_POWER_PIN 6
#define MAIN_TRIGGER_PIN 13
#define SOLENOID_POWER_PIN 12
/*
LiquidCrystal lcd(8, 7, 9, 3, 2, 1);

byte ammo = 12;

CRGB leds[NUM_LEDS];

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

  analogWrite(LCD_PWM_PIN, 50); //closer to 0 is brighter

  FastLED.setBrightness(30);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

  digitalWrite(LED_POWER_PIN, HIGH);

  leds[0] = CRGB::Blue;
  for (int i = 2; i < 14; i++) {
    leds[i] = CRGB::Blue;
    FastLED.show();
  }
  for (int i = 2; i < 8; i++) {
    leds[i].fadeLightBy(235);
    FastLED.show();
  }
}

void loop() {
  while (digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {
    digitalWrite(SOLENOID_POWER_PIN, HIGH);//enables solenoid
    digitalWrite(MOTOR_POWER_PIN, HIGH);//enables motor
    if (digitalRead(MAIN_TRIGGER_PIN) == HIGHanalogRead(A6) == LOW) {
      ammo--;
      leds[13 - ammo] = CRGB::Black;
      if (ammo == 0) {
        ammo = 12;
        leds[0] = CRGB::Blue;
        for (int i = 2; i < 14; i++) {
          leds[i] = CRGB::Blue;
          FastLED.show();
        }
        for (int i = 2; i < 8; i++) {
          leds[i].fadeLightBy(235);
          FastLED.show();
        }
      }
      FastLED.show();

      if (ammo < 10) {
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(1, 1);
      } else {
        lcd.setCursor(0, 1);
      }

      lcd.print(ammo);
      delay(42);//time to shoot one ball
      
      digitalWrite(SOLENOID_POWER_PIN, LOW);
      
      delay(100);//delay between rounds
    }
  }
  digitalWrite(MOTOR_POWER_PIN, LOW);

  // voltmeter
  int analog_value = analogRead(A7);
  float temp = (analog_value * 5.0) / 1024.0;
  float input_voltage = (float)temp / (51.0 / 151.0);
  if (input_voltage < 0.5)
  {
    input_voltage = 0.0;
  }
  lcd.setCursor(11, 1);
  lcd.print(input_voltage);
}*/

class LCD {
  private:
    LiquidCrystal lcd = LiquidCrystal(8, 7, 9, 3, 2, 1);
  public:
    LCD() {
      updateDisplay(12);
    }
    
    void updateDisplay(byte ammo) {
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print("Welcome, Alan!");
      if (ammo < 10) {
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(1, 1);
      } else {
        lcd.setCursor(0, 1);
      }
      lcd.print(ammo);
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
      lcd.setCursor(15, 1);
      lcd.print("V");
    }
};

class LEDStrip {
  private:
    CRGB leds[16];
  public:
    LEDStrip() {
      FastLED.setBrightness(30);
      FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);

      leds[0] = CRGB::Blue;
    }
    void updateStripLength(byte ammo) {
      for (byte  i = 2; i < 14; i++) {
        leds[i] = CRGB::Black;
      }
      for (byte  i = 2; i < ammo + 2; i++) {
        leds[i] = CRGB::Blue;
      }
      for (int i = 2; i < 8; i++) {
          leds[i].fadeLightBy(235);
      }
      FastLED.show();
    }
};

class Blaster {
  private:
    byte ammoCount;
    byte capacity;
    LCD lcd;
    LEDStrip ledStrip;
  public://make sure capacity <= 12
    Blaster(byte capacity) {
      this->capacity = capacity;
      this->ammoCount = capacity;
    }
    void reload() {
      ammoCount = capacity;
      lcd.updateDisplay(capacity);
      ledStrip.updateStripLength(capacity);
      delay(1000);
    }
    void fire() {
      if (ammoCount == 0) {
        reload();
      } else {
        lcd.updateDisplay(--ammoCount);
        ledStrip.updateStripLength(ammoCount);
        /*while(analogRead(A6) == LOW) {
          
        }*/
        delay(25);//time to shoot one ball
        digitalWrite(SOLENOID_POWER_PIN, LOW);        
      }
    }
    void updateVoltmeter() {
      lcd.updateVoltmeter();
    }
};

Blaster zeus(12);

void setup() {
  pinMode(MOTOR_POWER_PIN, OUTPUT);
  pinMode(LED_POWER_PIN, OUTPUT);
  pinMode(MOTOR_TRIGGER_PIN, INPUT);
  pinMode(MAIN_TRIGGER_PIN, INPUT);
  pinMode(LCD_PWM_PIN, OUTPUT);
  pinMode(SOLENOID_POWER_PIN, OUTPUT);

  analogWrite(LCD_PWM_PIN, 50); //closer to 0 is brighter

  digitalWrite(LED_POWER_PIN, HIGH);
}
void loop() {
  if (digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {
    digitalWrite(SOLENOID_POWER_PIN, HIGH);//enables solenoid
    digitalWrite(MOTOR_POWER_PIN, HIGH);//enables motor
    if (digitalRead(MAIN_TRIGGER_PIN) == HIGH) {
      zeus.fire();
      //Serial.println("fire!");
    }
  } else {
      digitalWrite(MOTOR_POWER_PIN, LOW);
  }
  zeus.updateVoltmeter();
}
