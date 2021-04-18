#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 1, 2, 3, 4);
const int pwm = 10; 

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {/*
  int i  = 12;
  while (i != 0){
   if(i < 10) {
    lcd.setCursor(0, 1);
    lcd.print(" ");
     lcd.setCursor(1, 1);
   } else {
    lcd.setCursor(0, 1);
   }
  lcd.print(i);
  i--;
  delay(1000);
  }
  i=12;
*/
  analogWrite(pwm,25) ;      //setting pwm to 25 
     delay(500) ;      //delay of 50 ms
     analogWrite(pwm,50) ;  
     delay(500) ; 
     analogWrite(pwm,75) ; 
     delay(500) ; 
     analogWrite(pwm,100) ; 
     delay(500) ; 
     analogWrite(pwm,125) ; 
     delay(500) ; 
     analogWrite(pwm,150) ; 
     delay(500) ; 
     analogWrite(pwm,175) ; 
     delay(500) ;
     analogWrite(pwm,200) ; 
     delay(500) ; 
     analogWrite(pwm,225) ; 
     delay(500) ; 
     analogWrite(pwm,250) ; 
}
