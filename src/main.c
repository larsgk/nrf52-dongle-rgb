#include <zephyr.h>

#include "rgb_led.h"

#define SLEEP_MS	2

void main(void)
{
	rgb_led_init();

	rgb_led_set(0,0xff,0);

	int8_t state = 0;
	int8_t mask = 0x7;
	int32_t val = 0;

	while (1) {
		k_sleep(SLEEP_MS);
		rgb_led_set(
			(mask & 0x1) ? val : 0,
			(mask & 0x2) ? val : 0,
			(mask & 0x4) ? val : 0);

		val += (state & 0x10) == 0 ? 2 : -2;

		if (val >= 0xFE) {
			state ^= 0x10;
		} else if (val < 0x01) {
			state ^= 0x10;

			// change color
			switch(mask) {
				case 0x1: mask = 0x2; break;
				case 0x2: mask = 0x4; break;
				case 0x4: mask = 0x7; break;
				default: mask = 0x1;
			}
		}
	}
}
