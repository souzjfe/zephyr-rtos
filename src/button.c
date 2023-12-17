/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "lib.h"
#include <inttypes.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

#define SW0_NODE DT_ALIAS(sw0)
#if !DT_NODE_HAS_STATUS(SW0_NODE, okay)
#error "Unsupported board: sw0 devicetree alias is not defined"
#endif

static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios, {0});
static struct gpio_callback button_cb_data;
static int32_t button_pressed_count = 0;

// LOG_MODULE_DECLARE(zbus, CONFIG_ZBUS_LOG_LEVEL);

// ZBUS_CHAN_DECLARE(button_data_chan);

static void button_pressed(const struct device *dev, struct gpio_callback *cb,
                           uint32_t pins) {
  button_pressed_count++;
  struct sensor_msg sm = {
      .count = button_pressed_count,
  };
  printk("%" PRIu32 "\n", button_pressed_count);
  // zbus_chan_pub(&button_data_chan, &sm, K_MSEC(250));
  // k_msleep(500);
}

int button_thread(void) {
  int ret;

  if (!gpio_is_ready_dt(&button)) {
    printk("Error: button device %s is not ready\n", button.port->name);
    return 0;
  }

  ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
  if (ret != 0) {
    printk("Error %d: failed to configure %s pin %d\n", ret, button.port->name,
           button.pin);
    return 0;
  }

  ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
  if (ret != 0) {
    printk("Error %d: failed to configure interrupt on %s pin %d\n", ret,
           button.port->name, button.pin);
    return 0;
  }

  gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
  gpio_add_callback(button.port, &button_cb_data);
  printk("Set up button at %s pin %d\n", button.port->name, button.pin);

  printk("Press the button\n");

  return 0;
}

K_THREAD_DEFINE(button_thread_id, STACKSIZE, button_thread, NULL, NULL, NULL,
                PRIORITY, 0, 0);