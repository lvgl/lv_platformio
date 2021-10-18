/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "lvgl.h"
#include "app_hal.h"

// #include "demo.h"
lv_obj_t *button;
lv_obj_t *label;
void myDemov8(){
  button = lv_btn_create(lv_scr_act());
  lv_obj_set_size(button,300,100);
  lv_obj_align(button,LV_ALIGN_CENTER,0,0);
  lv_obj_add_flag(button,LV_OBJ_FLAG_CLICKABLE);

  label = lv_label_create(button);
  lv_obj_align(label,LV_ALIGN_CENTER,0,0);
  lv_label_set_text_fmt(label,"LVGL 8.0.1 DEMO");
  lv_label_set_long_mode(label,LV_LABEL_LONG_WRAP );
}

int main(void)
{
	lv_init();

	hal_setup();

  myDemov8();
	// demo_create(); // not compatiblee v8.0.1

	hal_loop();
}
