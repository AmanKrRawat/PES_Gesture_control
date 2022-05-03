/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include "bluetoothconnection.h"
#include "ssd_display.h"
#include <lvgl.h>

enum states {menu_state, shape_state, game_state};
enum game_movements {stop,left,right,up,down};

int state = game_state;
int current_menu=0;
int game_move = stop;

void handle_data(char value)
{
	if(state == menu_state)
	{
		if(value == 'A')
		{
			printk("state %d value %d\n" , state, value);
			current_menu = 1;
		}
		if(value == 'B')
		{
			printk("state %d value %d\n" , state, value);
			current_menu = 0;
		}
		if(value == 'C')
		{
			printk("state %d value %d\n" , state, value);
			if(current_menu == 1)
				state = game_state;
			if(current_menu == 0)
				state = shape_state;
		}

	}
	if(state == game_state)
	{
		switch(value)
		{
			case 'L':	printk("state %d value %d\n" , state, value);
						game_move = left;
						break;
			case 'R':	printk("state %d value %d\n" , state, value);
						game_move = right;
						break;
			case 'U':	printk("state %d value %d\n" , state, value);
						game_move = up;
						break;
			case 'D':	printk("state %d value %d\n" , state, value);
						game_move = down;
						break;
			case 'S':	printk("state %d value %d\n" , state, value);
						game_move = stop;
						break;
			case 'B':	printk("state %d value %d\n" , state, value);
						game_move = stop;
						state = menu_state;
						break;
		}
	}
	if(state == shape_state)
	{
		switch(value){
			case 'S': break;
			case 'R': break;
			case 'L': break;
			case 'C': break;
			case 'B': break;
		}
	}
}

uint8_t notify_func(struct bt_conn *conn,
			   struct bt_gatt_subscribe_params *params,
			   const void *data, uint16_t length)
{
	if (!data) {
		printk("[UNSUBSCRIBED]\n");
		params->value_handle = 0U;
		return BT_GATT_ITER_STOP;
	}

	printk("[NOTIFICATION] data %s length %u\n", (char *)data, length);
	
	handle_data(((char *)data)[1]);

	return BT_GATT_ITER_CONTINUE;
}

void main(void)
{
	int err;
	err = bt_enable(NULL);
	

	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("Bluetooth initialized\n");

	start_scan();

	initialise_display();

	create_screens();

	while (1) {
		lv_task_handler();
		k_sleep(K_MSEC(10));
		update_screen();
		
	}
}
