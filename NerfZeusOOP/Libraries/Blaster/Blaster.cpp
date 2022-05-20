#include "Blaster.h"
#include <Arduino.h>
#include "LCD.h"
#include "LEDStrip.h"
#define SOLENOID_POWER_PIN 12

Blaster::Blaster(byte capacity) {
  this->capacity = capacity;
  this->ammoCount = capacity;
}
void Blaster::reload() {
  ammoCount = capacity;
  lcd.updateDisplay(capacity);
  ledStrip.updateStripLength(capacity);
  delay(1000);
}
void Blaster::fire() {
  if (ammoCount == 0) {
    reload();
  } else {
    lcd.updateDisplay(--ammoCount);
    ledStrip.updateStripLength(ammoCount);
    delay(25);//time to shoot one ball
    digitalWrite(SOLENOID_POWER_PIN, LOW);
  }
}
void Blaster::updateVoltmeter() {
  lcd.updateVoltmeter();
}
