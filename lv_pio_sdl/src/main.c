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
#include "driver.h"

#include "demo.h"

int main(void)
{
	lv_init();

	hw_init();

	demo_create();

	hw_loop();
}
