#include "ssd_display.h"

#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);


enum states {menu_state, shape_state, game_state};
enum game_movements {stop,left,right,up,down};
enum shapes {nothing, circle,tick, line, clear};

const struct device *display_dev;
static lv_point_t line_points[] = {{0, 2}, {5, 7}, {0, 12}};
static lv_point_t Game_line_points[] = {{1, 1}, {2, 1}};

lv_obj_t *menu_1_label;
lv_obj_t *menu_2_label;
int menu_1_label_x = 0 , menu_1_label_y = 0;
int menu_2_label_x = 0, menu_2_label_y = 15;
int menu_1_offset_x = 0 , menu_1_offset_y = 0;
int menu_2_offset_x = 0, menu_2_offset_y = 0;
int menu_selector_offset_x = 0, menu_selector_offset_y = 0;	
lv_obj_t * menu_line;
lv_obj_t * Game_line;
int x=0,y=0;

static lv_point_t square_points[] = {{0, 0}, {20, 0}, {20, 10}, {0, 10},{0,0}};
//static lv_point_t no_point[] = {{0,0},{0,0}};
static lv_point_t tick_points[] = {{0, 0}, {20, 8}, {60, 0}};
static lv_point_t line_shape_points[] = {{0, 10}, {127, 10}};

lv_obj_t * tick_shape;
lv_obj_t * square_shape;
lv_obj_t * line_shape;
lv_obj_t * no_shape;

int count=0;

void initialise_display(void)
{
    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return;
	}
}


void create_menu_screen(void)
{
    menu_1_label = lv_label_create(lv_scr_act());
	lv_label_set_text(menu_1_label, "SHAPE");
	lv_obj_align(menu_1_label, LV_ALIGN_TOP_LEFT, menu_1_label_x + menu_1_offset_x, menu_1_label_y + menu_1_offset_y);
	//lv_obj_set_size(menu_1_label, 128, 5);
	menu_2_label = lv_label_create(lv_scr_act());
	lv_label_set_text(menu_2_label, "CAR GAME");
	lv_obj_align(menu_2_label, LV_ALIGN_TOP_LEFT, menu_2_label_x + menu_2_offset_x, menu_2_label_y + menu_2_offset_y);	

	
    menu_line = lv_line_create(lv_scr_act());
    lv_line_set_points(menu_line, line_points, 3);     /*Set the points*/
	lv_obj_align(menu_line, LV_ALIGN_TOP_LEFT, 0, 0);
}

void create_game_screen(void)
{
    Game_line = lv_line_create(lv_scr_act());
    lv_line_set_points(Game_line, Game_line_points, 2);     /*Set the points*/
	lv_obj_align(Game_line, LV_ALIGN_TOP_LEFT, 0, 0);
}

void create_shape_screen(void)
{
	 
	 //no_shape = lv_line_create(lv_scr_act());
	 //lv_line_set_points(no_shape, no_point, 2);     /*Set the points*/
	 //lv_obj_center(no_shape);
	//  no_shape = lv_label_create(lv_scr_act());
	//  lv_label_set_text(no_shape, " ");
	//  lv_obj_center(no_shape);
	//  tick_shape = lv_line_create(lv_scr_act());
    //  lv_line_set_points(tick_shape, tick_points, 3);     /*Set the points*/
	//  lv_obj_center(tick_shape);
}

void create_line_shape_screen(void)
{
	line_shape = lv_line_create(lv_scr_act());
    lv_line_set_points(line_shape, line_shape_points, 2);     /*Set the points*/
	lv_obj_align(line_shape, LV_ALIGN_TOP_LEFT, 0, 0); 
}

void create_square_shape_screen(void)
{
	square_shape = lv_line_create(lv_scr_act());
    lv_line_set_points(square_shape, square_points, 5);     /*Set the points*/
	//lv_obj_align(square_shape, LV_ALIGN_TOP_LEFT, 0, 0); 	
	lv_obj_center(square_shape);
}

void create_tick_shape_screen(void)
{
	tick_shape = lv_line_create(lv_scr_act());
    lv_line_set_points(tick_shape, tick_points, 3);     /*Set the points*/
	//lv_obj_align(tick_shape, LV_ALIGN_TOP_LEFT, 0, 0); 	
	lv_obj_center(tick_shape);
}
void create_screens(void)
{
    create_menu_screen();
    //create_game_screen();
	//create_shape_screen();
    	
}

void update_menu_screen(void)
{
    if(current_menu == 1)
	{
		menu_1_offset_x = 0;
		menu_1_offset_y = 0;
		menu_2_offset_x = 15;
		menu_2_offset_y = 0;
		menu_selector_offset_x = 0;
		menu_selector_offset_y = 15;	
	}
	if(current_menu == 0)
	{
		menu_1_offset_x = 15;
		menu_1_offset_y = 0;
		menu_2_offset_x = 0;
		menu_2_offset_y = 0;
		menu_selector_offset_x = 0;
		menu_selector_offset_y = 0;	
	}
    lv_obj_align(menu_1_label, LV_ALIGN_TOP_LEFT, menu_1_label_x + menu_1_offset_x, menu_1_label_y + menu_1_offset_y);
	lv_obj_align(menu_2_label, LV_ALIGN_TOP_LEFT, menu_2_label_x + menu_2_offset_x, menu_2_label_y + menu_2_offset_y);
	lv_obj_align(menu_line, LV_ALIGN_TOP_LEFT, menu_selector_offset_x, menu_selector_offset_y);	
}

void update_game_screen(void)
{
    switch(game_move)
	{
		case left: lv_obj_align(Game_line, LV_ALIGN_TOP_LEFT, x, y);
				x--;
				if(x < 0)
				{
					x = 0;
				}
				break;
		case right: lv_obj_align(Game_line, LV_ALIGN_TOP_LEFT, x, y);
				x++;
				if(x > 126)
				{
					x = 126;
				}
				break;
		case down: lv_obj_align(Game_line, LV_ALIGN_TOP_LEFT, x, y);
				y++;
				if(y > 29)
				{
					y = 29;
				}
				break;
		case up: lv_obj_align(Game_line, LV_ALIGN_TOP_LEFT, x, y);
				y--;
				if(y < 0)
				{
					y = 0;
				}
				break;
		case stop: lv_obj_align(Game_line, LV_ALIGN_TOP_LEFT, 0, 0);
				break;
			
	}    
}

void update_shape_screen(void)
{
    if(shape == nothing)
	{

	}
	if(shape == circle)
	{

	}
	if(shape == line)
	{

	}
	if(shape == tick)
	{

	}
	if(shape == clear)
	{

	}
    
}

void update_screen(void)
{
	//printf("%d\n", state);
    if(state == menu_state)
	{	
		update_menu_screen();
	}
    if(state == game_state)
    {
        update_game_screen();
    }
	if(state == shape_state)
    {
        update_shape_screen();
    }

}