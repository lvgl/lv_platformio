/**
 * @file demo.h
 *
 */

#ifndef DEMO_H
#define DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#if defined(LV_CONF_INCLUDE_SIMPLE) || defined(ARDUINO)
#include <lvgl.h>
#else
#include "../../../lvgl/lvgl.h"
#endif


/*********************
 *      DEFINES
 *********************/
#define LV_USE_DEMO 1
#define LV_DEMO_WALLPAPER  1
#if (LV_COLOR_DEPTH < 16) || defined(ESP8266)
#undef  LV_DEMO_WALLPAPER
#define LV_DEMO_WALLPAPER  0
#endif
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a demo application
 */
void demo_create(void);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif
