#include "LCD.h"
#include <LiquidCrystal.h>
#include <Arduino.h>

LCD::LCD(uint8_t rs,  uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3): LiquidCrystal(rs, enable, d0, d1, d2, d3) {
  begin(16, 2);
  print("Welcome, Alan!");
}

void LCD::updateDisplay(byte ammo) {
  if (ammo < 10) {
    setCursor(0, 1);
    print(" ");
    setCursor(1, 1);
  } else {
    setCursor(0, 1);
  }
  print(ammo);
}

void LCD::updateVoltmeter() {
  int analog_value = analogRead(A7);
  float temp = (analog_value * 5.0) / 1024.0;
  float input_voltage = (float)temp / (51.0 / 151.0);
  if (input_voltage < 0.5)
  {
    input_voltage = 0.0;
  }
  setCursor(11, 1);
  print(input_voltage);
  setCursor(15, 1);
  print("V");
}
