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
#include <stdlib.h>
#include <math.h>
#include "bluetooth_file.h"
#include "window.h"
#include "classifier.h"
#include "button_config.h"
float sample[6] = {0};

const uint16_t features_count = 48;
float features[48];
uint16_t head = 0;
float queue[312];

enum states {menu_state, shape_state, game_state};
enum game_movements {stop,left,right,up,down};
enum shapes {nothing, circle, tick, line};
int state = menu_state;
int current_menu = 0;
int game_move = stop;
int shape = nothing;
char send_command=0;
char send_command_old=0;
int button_press = 0;

double theta_x;
double theta_y;
double theta_z;
double arx, ary, arz;
double rx, ry, rz;

extern void button_init();

static void command_notify(char menu)
{
	bt_hrs_notify(menu);
}
void get_accel_values(void)
{

}
void get_gyro_values(void)
{
	if(rx<-25)
	{
		printf("right\n");
		send_command= 'R';
	}

	else if(rx>25)
	{
		printf("left\n");
		send_command= 'L';
	}

	else if(ry>25)
	{
		printf("up\n");
		send_command= 'U';
	}

	else if(ry<-25)
	{
		printf("down\n");
		send_command= 'D';
	}
}

void identify_shape()
{
	if (!transform(sample))
      	{
                  //Data not yet ready
		}
		else{
		// predict gesture
		printf("Gesture: ");
		printf(predictLabel(features));
		printf("\n");
		//hrs_notify('D');
		}

}
void handle_data(void)
{
	if(state == menu_state)
	{
		get_gyro_values();
		if(button_press == 1)
 		{
 			button_press = 0;
			send_command = 'C';
			if(current_menu == 0)
				state = shape_state;
			if(current_menu == 1)
				state = game_state;
 		}
 		if(button_press == 2)
 		{
 			state = menu_state;
 			button_press = 0;
 		}
	}
	else if(state == game_state)
	{
		get_gyro_values();
		if(button_press == 1)
		{
			send_command = 'C';
			game_move = stop;
			button_press = 0;
		}
		if(button_press == 2)
		{
			send_command = 'B';
			game_move = stop;
			button_press = 0;
			state = menu_state;
		}
	}
	else if(state == shape_state)
	{
		identify_shape();
		if(button_press == 1)
		{
			send_command = 'C';
			shape = nothing;
			button_press = 0;
		}
		if(button_press == 2)
		{
			send_command = 'B';
			shape = nothing;
			button_press = 0;
			state = menu_state;
		}
	}
	if(send_command != send_command_old)
	{
		if(state == menu_state && send_command == 'D')
		{
			current_menu = 1;
		}
		if(state == menu_state && send_command == 'U')
		{
			current_menu = 0;
		}
		command_notify(send_command);
	}
	send_command_old = send_command;
}

static int process_mpu6050(const struct device *dev)
{
	struct sensor_value accel[3];
	struct sensor_value gyro[3];
	int rc = sensor_sample_fetch(dev);

	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);
	}
	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_GYRO_XYZ, gyro);
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
	theta_x = theta_x + sample[3]*0.05/1000;
    theta_y = theta_y + sample[4]*0.05/1000;
	theta_z = theta_z + sample[5]*0.05/1000;

	arx = (180/3.141592) * atan(sample[0] / sqrt(sample[1]*sample[1] + sample[2]*sample[2])); 
	ary = (180/3.141592) * atan(sample[1] / sqrt(sample[0]*sample[0] + sample[2]*sample[2]));
	arz = (180/3.141592) * atan(sqrt(sample[1]*sample[1] + sample[0]*sample[0]) / sample[2]);
	rx = (0.96 * arx) + (0.04 * theta_x);
    ry = (0.96 * ary) + (0.04 * theta_y);
    rz = (0.96 * arz) + (0.04 * theta_z);
	printf("%f %f %f", arx, ary, arz);
	handle_data();
	return rc;
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

	button_init();

	if (!mpu6050) {
		printf("Failed to find sensor %s\n", label);
		return;
	}

	/* Implement notification. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */
	while (1) {
		k_sleep(K_SECONDS(0.05));
		int rc = process_mpu6050(mpu6050);
		
	}
}
