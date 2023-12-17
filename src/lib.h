/*
 * Copyright (c) 2022 Rodrigo Peixoto <rodrigopex@gmail.com>
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _LIB_H_
#define _LIB_H_
#include <stdint.h>
#include <zephyr/kernel.h>

// configs que geravam warn nas threads
#define ARCH_STACK_PTR_ALIGN 8
#define CONFIG_SYS_CLOCK_TICKS_PER_SEC 100
// configs que geravam warn no zbus
#define CONFIG_NUM_PREEMPT_PRIORITIES 15

#define SLEEP_TIME_MS 1
#define STACKSIZE 1024
#define PRIORITY 7

struct version_msg {
  uint8_t major;
  uint8_t minor;
  uint16_t build;
};

struct sensor_msg {
  uint32_t count;
};

#endif /* _LIB_H_ */
