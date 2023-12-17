#include "lib.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios, {0});

int led_status_thread(void) {
  int ret;

  if (!gpio_is_ready_dt(&led)) {
    printk("Error: LED device %s is not ready\n", led.port->name);
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT);

  if (ret != 0) {
    printk("Error %d: failed to configure %s pin %d\n", ret, led.port->name,
           led.pin);
    return 0;
  }

  while (1) {
    gpio_pin_toggle_dt(&led);
    k_msleep(1000);
  }

  return 0;
}

K_THREAD_DEFINE(led_status_id, STACKSIZE, led_status_thread, NULL, NULL, NULL,
                PRIORITY, 0, 0);