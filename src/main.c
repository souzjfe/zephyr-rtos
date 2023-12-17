#include "lib.h"
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util_macro.h>
#include <zephyr/zbus/zbus.h>
// LOG_MODULE_DECLARE(zbus, CONFIG_ZBUS_LOG_LEVEL);

// ZBUS_CHAN_DEFINE(button_data_chan,  /* Name */
//                  struct sensor_msg, /* Message type */

//                  NULL,                                /* Validator */
//                  NULL,                                /* User data */
//                  ZBUS_OBSERVERS(thread_handler1_sub), /* observers */
//                  ZBUS_MSG_INIT(0)                     /* Initial value {0} */
// );

// static void fh1_cb(const struct zbus_channel *chan) {
//   const struct sensor_msg *msg = zbus_chan_const_msg(chan);

//   LOG_INF("Sensor msg processed by CALLBACK fh1: %u", msg->count);
// }
// ZBUS_LISTENER_DEFINE(fast_handler1_lis, fh1_cb);
// struct sensor_wq_info {
//   struct k_work work;
//   const struct zbus_channel *chan;
//   uint8_t handle;
// };
// static struct sensor_wq_info wq_handler1 = {.handle = 1};
// static void wq_dh_cb(struct k_work *item) {
//   struct sensor_msg msg;
//   struct sensor_wq_info *sens = CONTAINER_OF(item, struct sensor_wq_info,
//   work);

//   zbus_chan_read(sens->chan, &msg, K_MSEC(200));
//   LOG_INF("Sensor msg processed by WORK QUEUE handler dh: %u", msg.count);
// }
// static void dh1_cb(const struct zbus_channel *chan) {
//   wq_handler1.chan = chan;

//   k_work_submit(&wq_handler1.work);
// }
// ZBUS_LISTENER_DEFINE(delay_handler1_lis, dh1_cb);
int main() {
  /* code */
  // k_work_init(&wq_handler1.work, wq_dh_cb);

  return 0;
}
// ZBUS_SUBSCRIBER_DEFINE(thread_handler1_sub, 4);

// static void thread_handler1_task(void) {
//   const struct zbus_channel *chan;

//   while (!zbus_sub_wait(&thread_handler1_sub, &chan, K_FOREVER)) {
//     struct sensor_msg msg;

//     zbus_chan_read(chan, &msg, K_MSEC(200));

//     LOG_INF("Sensor msg processed by THREAD handler dh: %u", msg.count);
//   }
// }

// K_THREAD_DEFINE(thread_handler1_id, 1024, thread_handler1_task, NULL, NULL,
//                 NULL, 7, 0, 0);
