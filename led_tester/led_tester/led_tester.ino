#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 16

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 11

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
    //FastLED.setBrightness(7);
    FastLED.setMaxPowerInMilliWatts(100);
    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
}

void loop() { 
  // Turn the LED on, then pause
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(100);
  }
  // Now turn the LED off, then pause
  for (int i = NUM_LEDS; i > 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
}
