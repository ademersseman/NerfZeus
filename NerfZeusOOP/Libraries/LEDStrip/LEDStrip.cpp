#include "LEDStrip.h"
#include "FastLED.h"
#define NUM_LEDS 16
#define LED_DATA_PIN 11

LEDStrip::LEDStrip() {
  FastLED.setBrightness(30);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);

  leds[0] = CRGB::Blue;
}
void LEDStrip::updateStripLength(byte ammo) {
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
