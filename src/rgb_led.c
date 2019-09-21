#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <drivers/pwm.h>


#if defined(DT_NORDIC_NRF_PWM_PWM_0_LABEL) && defined(DT_NORDIC_NRF_PWM_PWM_0_CH0_PIN)
#define PWM_DRIVER	DT_NORDIC_NRF_PWM_PWM_0_LABEL
#define RED_PIN     DT_NORDIC_NRF_PWM_PWM_0_CH0_PIN
#define GREEN_PIN   DT_NORDIC_NRF_PWM_PWM_0_CH1_PIN
#define BLUE_PIN    DT_NORDIC_NRF_PWM_PWM_0_CH2_PIN
#else
#error "NRF PWM config not found"
#endif

#define PERIOD (USEC_PER_SEC / 100)

struct device *pwm_dev;

void rgb_led_init()
{
    pwm_dev = device_get_binding(PWM_DRIVER);

	if (!pwm_dev) {
		printk("Cannot find PWM device!\n");
		return;
	}
}

void rgb_led_set(u32_t r, u32_t g, u32_t b)
{
    if( pwm_pin_set_usec(pwm_dev, RED_PIN, PERIOD, ((255 - (r & 0xff)) * PERIOD) >> 8) != 0 ||
        pwm_pin_set_usec(pwm_dev, GREEN_PIN, PERIOD, ((255 - (g & 0xff)) * PERIOD) >> 8) != 0 ||
        pwm_pin_set_usec(pwm_dev, BLUE_PIN, PERIOD, ((255 - (b & 0xff)) * PERIOD) >> 8) != 0) {
        printk("PWM pin write fails!\n");
		return;
    }
}