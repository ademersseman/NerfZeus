#ifndef Blaster_h
#define Blaster_h
#include <Arduino.h>
#include "LCD.h"
#include "LEDStrip.h"

class Blaster {
  private:
    byte ammoCount;
    byte capacity;
    LCD lcd;
    LEDStrip ledStrip;
  public:
    Blaster(byte capacity);
    void reload();
    void fire();
    void updateVoltmeter();
};
#endif
