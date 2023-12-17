#include "lib.h"
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <zephyr/zbus/zbus.h>

LOG_MODULE_DECLARE(zbus, CONFIG_ZBUS_LOG_LEVEL);

ZBUS_CHAN_DEFINE(sensor_data_chan, u_int32_t, NULL, NULL,
                 ZBUS_OBSERVERS(listener_example), /* observers */
                 ZBUS_MSG_INIT(0)                  /* Initial value {0} */
);
static int cmd_led(const struct shell *shell, size_t argc, char **argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);

  shell_print(shell, "Ligar LED\n");

  k_msleep(200);
  return 0;
}

SHELL_CMD_ARG_REGISTER(led, NULL, "Description: Pisca um Led", cmd_led, 1, 0);

static void cmd_demo_on(const struct shell *shell, size_t argc, char **argv) {
  uint32_t sm = 14;

  printk("ADC ligado");
  zbus_chan_pub(&sensor_data_chan, &sm, K_MSEC(200));
}
static void cmd_demo_off(const struct shell *shell, size_t argc, char **argv) {
  printk("ADC desligado");
}

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_demo, SHELL_CMD(on, NULL, "Print params command.", cmd_demo_on),
    SHELL_CMD(off, NULL, "Ping command.", cmd_demo_off), SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(demo, &sub_demo, "Demo commands", NULL);

ZBUS_SUBSCRIBER_DEFINE(thread_handler1_sub, 4);
static void listener_callback_example(const struct zbus_channel *chan) {
  const uint32_t *sm = zbus_chan_const_msg(chan);

  LOG_INF("From listener -> Acc x=%i,", &sm);
}
ZBUS_LISTENER_DEFINE(listener_example, listener_callback_example);
