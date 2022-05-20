#include <LCD.h>

LCD lcd(8, 7, 9, 3, 2, 1);
unsigned int x = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("in the loop");
  lcd.updateDisplay(12);
}

void loop() {
  lcd.clear();
  if (x == 10) {
    x = 0;
  }
  lcd.print("x: " + x);
  delay(250);
}
