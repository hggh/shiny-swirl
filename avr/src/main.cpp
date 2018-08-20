#include <Arduino.h>
#include <avr/power.h>
#include "FastLED.h"

#define WS2812_PIN 6
#define PIN_MOTION 2
#define NUM_LEDS 31

CRGB leds[NUM_LEDS];
volatile uint8_t hue = 0;
volatile uint8_t update_leds = 0;
static uint8_t led_brightness = 150;

ISR(TIMER1_COMPA_vect) {
	update_leds = 1;
	fill_rainbow(leds, NUM_LEDS, hue++, 5);
}

void int_handler() {
}

// ~ 22ms
void setup_timer1() {
	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	OCR1A = 170;
	TCCR1B |= _BV(WGM12);
	TCCR1B |= _BV(CS10);
	TCCR1B |= _BV(CS12);
	TIMSK1 |= _BV(OCIE1A);
	interrupts();
}

void setup() {
	// disable ADC
	ADCSRA &= ~(1 << 7);
	power_adc_disable();

	power_spi_disable();
	power_twi_disable();
	power_usart0_disable();

	randomSeed(analogRead(0));
	pinMode(PIN_MOTION, INPUT);

	attachInterrupt(digitalPinToInterrupt(PIN_MOTION), int_handler, FALLING);

	FastLED.addLeds<WS2812B, WS2812_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(led_brightness);

	setup_timer1();
}

void loop() {
	if (update_leds == 1) {
		update_leds = 0;
		FastLED.show();
	}
}
