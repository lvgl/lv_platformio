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

#if defined(ARDUINO_ARCH_ESP8266)
extern "C" void setup();
extern "C" void loop();
#endif

void setup()
{
	lv_init();

	hw_init();

	demo_create();
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
