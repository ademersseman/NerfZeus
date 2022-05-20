#include <LCD.h>
#include "LEDStrip.h"

#define NUM_LEDS 16
#define LED_DATA_PIN 11
#define LED_POWER_PIN 10
#define LCD_PWM_PIN 5
#define MOTOR_TRIGGER_PIN 4
#define MOTOR_POWER_PIN 6
#define MAIN_TRIGGER_PIN 13
#define SOLENOID_POWER_PIN 12


class Blaster {
  private:
    void updateDisplay(byte ammo) {
      if (ammo < 10) {
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(1, 1);
      } else {
        lcd.setCursor(0, 1);
      }
      lcd.print(ammo);
    }
    void reload() {
      ammoCount = capacity;
      updateDisplay(capacity);
      ledStrip.updateStripLength(capacity);
      delay(1000);
    }
    byte ammoCount;
    byte capacity;
    LCD lcd;
    LEDStrip ledStrip;
  public:
  Blaster(byte capacity): lcd(8, 7, 9, 3, 2, 1) {
    this->capacity = capacity;
    this->ammoCount = capacity;
  }
  void fire() {
    if (ammoCount == 0) {
      reload();
    } else {
      updateDisplay(--ammoCount);
      ledStrip.updateStripLength(ammoCount);
      delay(25);//time to shoot one ball
      digitalWrite(SOLENOID_POWER_PIN, LOW);
      delay(700);
    } 
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

Blaster zeus(12);

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_POWER_PIN, OUTPUT);
  pinMode(LED_POWER_PIN, OUTPUT);
  pinMode(MOTOR_TRIGGER_PIN, INPUT);
  pinMode(MAIN_TRIGGER_PIN, INPUT);
  pinMode(LCD_PWM_PIN, OUTPUT);
  pinMode(SOLENOID_POWER_PIN, OUTPUT);

  digitalWrite(LED_POWER_PIN, HIGH);
}
void loop() {
  Serial.print("triggered");
  if (digitalRead(MOTOR_TRIGGER_PIN) == HIGH) {
    Serial.print("triggered");
    digitalWrite(SOLENOID_POWER_PIN, HIGH);//enables solenoid
    digitalWrite(MOTOR_POWER_PIN, HIGH);//enables motor
    if (digitalRead(MAIN_TRIGGER_PIN) == HIGH) {
      zeus.fire();
    }
  } else {
      digitalWrite(MOTOR_POWER_PIN, LOW);
  }
  zeus.updateVoltmeter();
}
