#ifndef LEDStrip_h
#define LEDStrip_h
#include "FastLED.h"

class LEDStrip {
  private:
    CRGB leds[16];
  public:
    LEDStrip();
    void updateStripLength(byte ammo);
};

#endif
