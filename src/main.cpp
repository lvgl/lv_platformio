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

#include "lv_test_group.h"
#include "sysmon.h"
#include "round_buttons.h"

#if defined(ARDUINO_ARCH_ESP8266)
extern "C" void setup();
extern "C" void loop();
#endif

void setup()
{
	lv_init();

	hw_init();

	//demo_create();
	lv_test_group_1(rotary_group_get());
	//sysmon_create();
	//round_buttons();
}

void loop()
{
  hw_loop();
}

#if ! defined(ARDUINO)
int main(void)
{
  setup();
  while(1) {
  	loop();
  }
}
#endif
