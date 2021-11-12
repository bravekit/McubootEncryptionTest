/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
west sign --tool imgtool --tool-path "C:\NordicNrf\v1.7.0\bootloader\mcuboot\scripts\imgtool.py" --build-dir "C:\MyWorkC\TenniRoboAll\Firmware\NRF52\NrfZephyr\bootloaderTest\build" --header-size 0x200 -S 0x40000 --key "C:\MyWorkC\TenniRoboAll\Firmware\NRF52\NrfZephyr\bootloaderTest\root-rsa-2048.pem" 

sign --key "C:\MyWorkC\TenniRoboAll\Firmware\NRF52\NrfZephyr\bootloaderTest\root-rsa-2048.pem"  --header-size 0x200 -S 0x40000 --align 8 --version 1.3 -E "C:\MyWorkC\TenniRoboAll\Firmware\NRF52\NrfZephyr\bootloaderTest\enc-rsa2048-pub.pem" signed-zephyr-1.3.hex

*/

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include "bluetooth.h"

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif

void main(void)
{
	const struct device *dev;
	bool led_is_on = true;
	int ret;

	dev = device_get_binding(LED0);
	if (dev == NULL) {
		return;
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}

#ifdef CONFIG_MCUMGR_CMD_OS_MGMT
	os_mgmt_register_group();
#endif
#ifdef CONFIG_MCUMGR_CMD_IMG_MGMT
	img_mgmt_register_group();
#endif
#ifdef CONFIG_MCUMGR_CMD_STAT_MGMT
	stat_mgmt_register_group();
#endif

	bluetooth_init();
	while (1) {
		gpio_pin_set(dev, PIN, (int)led_is_on);
		led_is_on = !led_is_on;
		//k_msleep(SLEEP_TIME_MS);
		k_msleep(50);
	}
}
