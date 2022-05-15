/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>
#include <device.h>
#include <stdio.h>
#include <drivers/sensor.h>

#include "window.h"
#include "classifier.h"
#include "bluetooth_file.h"


float sample[6] = {0};

const uint16_t features_count = 48;
float features[48];
uint16_t head = 0;
float queue[246];


                    



static int process_mpu6050(const struct device *dev)
{
	struct sensor_value accel[3];
	struct sensor_value gyro[3];
	int rc = sensor_sample_fetch(dev);

	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ,
					accel);
	}
	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_GYRO_XYZ,
					gyro);
	}
	if (rc == 0) {
		/*printf("%f,%f,%f,%f,%f,%f\n",
		       sensor_value_to_double(&accel[0]),
		       sensor_value_to_double(&accel[1]),
		       sensor_value_to_double(&accel[2]),
		       sensor_value_to_double(&gyro[0]),
		       sensor_value_to_double(&gyro[1]),
		       sensor_value_to_double(&gyro[2])); */
	} else {
		printf("sample fetch/get failed: %d\n", rc);
	}
	sample[0] = sensor_value_to_double(&accel[0]);
	sample[1] = sensor_value_to_double(&accel[1]);
	sample[2] = sensor_value_to_double(&accel[2]);
	sample[3] = sensor_value_to_double(&gyro[0]);
	sample[4] = sensor_value_to_double(&gyro[1]);
	sample[5] = sensor_value_to_double(&gyro[2]);


	return rc;
}





static void bas_notify(void)
{
	char menu = 'E';
	bt_bas_set_battery_level(menu);
}

static void hrs_notify(char menu)
{
	//char menu = 'D';
	bt_hrs_notify(menu);
}

void main(void)
{
	int err;

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

	bt_conn_auth_cb_register(&auth_cb_display);


	const char *const label = DT_LABEL(DT_INST(0, invensense_mpu6050));
	const struct device *mpu6050 = device_get_binding(label);

	if (!mpu6050) {
		printf("Failed to find sensor %s\n", label);
		return;
	}

	/* Implement notification. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */
	while (1) {
		k_sleep(K_SECONDS(0.05));

		/* Heartrate measurements simulation */
		//hrs_notify('D');
		//k_sleep(K_SECONDS(1));
		/* Battery level simulation */
		//bas_notify();
		//hrs_notify('E');
		if (!transform(sample))
      		{
                  //Data not yet ready
			}
		else{
		// predict gesture
		printf("Gesture: ");
		printf(predictLabel(features));
		printf("\n");
		hrs_notify('D');
		}
	}
}
