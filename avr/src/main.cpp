#include <Arduino.h>
#include <avr/power.h>
#include "FastLED.h"

#define WS2812_PIN 6
#define NUM_LEDS 31
CRGB leds[NUM_LEDS];
volatile uint8_t hue = 0;

void setup() {
	// disable ADC
	ADCSRA &= ~(1 << 7);
	power_adc_disable();

	power_spi_disable();

	FastLED.addLeds<WS2812B, WS2812_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(150);
}

void loop() {
	fill_rainbow(leds, NUM_LEDS, hue++, 5);
	FastLED.show();
	delay(20);
}
