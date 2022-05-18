#ifndef __DISPLAY__
#define __DISPLAY__

#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>

extern void initialise_display(void);
extern void create_screens(void);

extern void update_screen(void);
extern const struct device *display_dev;
extern lv_obj_t * menu_1_label;
extern lv_obj_t * menu_2_label;
extern lv_obj_t * menu_line;
extern lv_obj_t * Game_line;

extern lv_obj_t * tick_shape;
extern lv_obj_t * circle_shape;
extern lv_obj_t * line_shape;
extern lv_obj_t * no_shape;
extern int count;
extern int menu_1_label_x , menu_1_label_y;
extern int menu_2_label_x, menu_2_label_y ;
extern int menu_1_offset_x , menu_1_offset_y;
extern int menu_2_offset_x , menu_2_offset_y;
extern int menu_selector_offset_x , menu_selector_offset_y ;	


extern int state;
extern int current_menu;
extern int game_move;
extern int shape;

extern void create_game_screen(void);

#endif