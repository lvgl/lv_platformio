/**
 * \file    lvdrv-rotarygrp.h
 * \brief   Rotary group for LittlevGL
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-02-03
 * \copyright GPL/BSD
 */

#ifndef _LITTLEVGL_DRV_ROTARY_GROUP_H
#define _LITTLEVGL_DRV_ROTARY_GROUP_H 1

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

void rotary_group_init(lv_indev_t* encoder_indev);
void rotary_group_add(lv_obj_t * obj);
lv_group_t *rotary_group_get();

bool rotary_encoder_lv_read(lv_indev_drv_t * drv, lv_indev_data_t*data);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif // _LITTLEVGL_DRV_ROTARY_GROUP_H


