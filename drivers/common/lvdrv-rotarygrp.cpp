/**
 * \file    lvdrv-rotarygrp.cpp
 * \brief   Rotary group for LittlevGL
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-02-03
 * \copyright GPL/BSD
 */

#include "lvgl.h"
#include "lvdrv-rotarygrp.h"

////////////////////////////////////////////////////////////////////////////////
#include "setuprotary.h"

/* Reading input device (simulated encoder here) */
bool rotary_encoder_lv_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
  data->state = LV_INDEV_STATE_REL;

#if USE_ROTARY
  data->enc_diff = get_encoder()->get_diff();

  //if(get_encoder()->get_btn()) data->state = LV_INDEV_STATE_PR;
  if(get_encoder()->isPressed()) data->state = LV_INDEV_STATE_PR;

#else // USE_ROTARY
  data->enc_diff = 0;
#endif // USE_ROTARY

  return false; /*No buffering now so no more data read*/
}

////////////////////////////////////////////////////////////////////////////////
static lv_group_t* grp_enc = nullptr; //An Object Group

lv_group_t *rotary_group_get() { return grp_enc; }

void rotary_group_init(lv_indev_t* encoder_indev)
{
    // create Group for encoder
    if (grp_enc == nullptr) {
      grp_enc = lv_group_create();
    }
    lv_group_set_wrap(grp_enc, true);
    lv_indev_set_group(encoder_indev, grp_enc);
}

void rotary_group_add(lv_obj_t * obj)
{
  //ADD object TO GROUP enc
  lv_group_add_obj(grp_enc, obj);
}

////////////////////////////////////////////////////////////////////////////////
