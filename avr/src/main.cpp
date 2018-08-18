#include <Arduino.h>
#include <avr/power.h>
#include "FastLED.h"

#define WS2812_PIN 6
#define NUM_LEDS 10
CRGB leds[NUM_LEDS];

void setup() {
	// disable ADC
	ADCSRA &= ~(1 << 7);
	power_adc_disable();

	power_spi_disable();

	FastLED.addLeds<WS2812B, WS2812_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
	CRGB color(255, 0, 0);
	fill_solid(leds, NUM_LEDS, color);
	FastLED.setBrightness(80);
	FastLED.show();
}
