/**
 * @file lv_test_group.h
 *
 */

#ifndef LV_TEST_GROUP_H
#define LV_TEST_GROUP_H

#ifdef __cplusplus
extern "C" {
#endif

#define LV_USE_GROUP 1
#define LV_USE_TESTS 1

#include "lvgl.h"
lv_group_t *lv_test_group_1(lv_group_t *g);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TEST_BAR_H*/
