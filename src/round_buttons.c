/**
 * \file    round_buttons.c
 * \brief   buttons in a circle
 * \date    2020-03-02
 * \copyright GPL/BSD
 */
#include "lvgl.h"
#include "driver.h"
#include "round_buttons.h"

void round_buttons(void)
{
	lv_obj_t * circle,*btn,*label,*img;
	static lv_style_t circle_style,rel_style,prs_style;
	circle=lv_obj_create(lv_scr_act(),NULL);
	int r = TFT_WIDTH;
	if (r > TFT_HEIGHT) r = TFT_HEIGHT;
	r = r / 2;
	lv_obj_set_size(circle, r*2, r*2);
	int x = (1 - 0.70710678) * r; // sin(pi/4) = 0.70710678

	lv_style_copy(&circle_style,&lv_style_pretty_color);
	lv_style_btn_rel.body.radius=LV_RADIUS_CIRCLE;
	lv_style_btn_pr.body.radius=LV_RADIUS_CIRCLE;
	circle_style.body.radius=LV_RADIUS_CIRCLE;
	lv_obj_set_style(circle, &circle_style);
	lv_obj_align(circle, NULL, LV_ALIGN_CENTER, 0, 0);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_TOP_MID, 0, 0);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_UP);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_TOP_RIGHT, -x,x);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_BLUETOOTH);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_RIGHT_MID, 0, 0);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_RIGHT);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_BOTTOM_RIGHT, -x,-x);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_BATTERY_FULL);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_DOWN);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_BOTTOM_LEFT, x,-x);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_SETTINGS);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_LEFT_MID, 0, 0);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_LEFT);

	btn=lv_btn_create(circle, NULL);
	lv_obj_set_size(btn, 60, 60);
	rotary_group_add(btn);
	lv_btn_set_style(btn, LV_BTN_STATE_REL, &lv_style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STATE_PR, &lv_style_btn_pr);
	lv_obj_align(btn, circle, LV_ALIGN_IN_TOP_LEFT, x,x);
	img = lv_img_create(btn, NULL);
	lv_img_set_auto_size(img, true);
	lv_obj_set_click(img, false);
	lv_img_set_src(img, LV_SYMBOL_WIFI);
}

