#ifndef __DISPLAY__
#define __DISPLAY__

#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>

extern void initialise_display(void);
extern void create_screens(void);

extern void update_screen(void);
extern const struct device *display_dev;
extern lv_obj_t *menu_1_label;
extern lv_obj_t *menu_2_label;
extern int count;
extern int menu_1_label_x , menu_1_label_y;
extern int menu_2_label_x, menu_2_label_y ;
extern int menu_1_offset_x , menu_1_offset_y;
extern int menu_2_offset_x , menu_2_offset_y;
extern int menu_selector_offset_x , menu_selector_offset_y ;	
extern lv_obj_t * line1;


extern int state;
extern int current_menu;
extern int game_move;


#endif