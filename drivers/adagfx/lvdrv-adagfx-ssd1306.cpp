/**
 * \file    lvdrv-adagfx-ssd1306.cpp
 * \brief   SSD1306 driver for LittlevGL
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-02-03
 * \copyright GPL/BSD
 */
#include "lvgl.h"
#include "lvdrv-adagfx-ssd1306.h"
#include "setuprotary.h"
#include "lvdrv-rotarygrp.h"

////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 //4 // Reset pin # (or -1 if sharing Arduino reset pin)

#if defined(ARDUINO_ARCH_ESP32)
#define USE_ESP32_HELTEC_LORA2 1
#endif

#if defined(USE_ESP32_HELTEC_LORA2)
#define I2C_SDA 4 // heltec WIFI LoRa 32(V2)
#define I2C_SCL 15 // heltec WIFI LoRa 32(V2)
TwoWire twi = TwoWire(1);

void init_heltec_lora2() {
#if 0
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 to high
#else
#undef OLED_RESET
#define OLED_RESET     16
#endif
  twi.begin(I2C_SDA, I2C_SCL);
}

#define PTR_WIRE (&twi)

#else
#define init_heltec_lora2()
#define PTR_WIRE (&Wire)
#endif

Adafruit_SSD1306 display(LV_HOR_RES_MAX,LV_VER_RES_MAX, PTR_WIRE, OLED_RESET);

/**
 * Flush a buffer to the marked area
 * @param drv pointer to driver where this function belongs
 * @param area an area where to copy `color_p`
 * @param color_p an array of pixel to copy to the `area` part of the screen
 */
void cb_flush_adagfx(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    int row, col;
    lv_color_t * p = color_p;
    for (row = area->y1; row <= area->y2; row++) {
      for (col = area->x1; col <= area->x2; col++) {
        if (lv_color_brightness(*p) < 128) {
        //if (*p == LV_COLOR_BLACK) {
            display.drawPixel(col, row, SSD1306_BLACK);
        } else {
            display.drawPixel(col, row, SSD1306_WHITE);
        }
        p ++;
      }
    }
    
    lv_disp_flush_ready(disp_drv);
}

void cb_rounder_adagfx(struct _disp_drv_t * disp_drv, lv_area_t *a)
{
    a->x1 = a->x1 & ~(0x7);
    a->x2 = a->x2 |  (0x7);
}

void cb_set_px_adagfx(struct _disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
    buf += buf_w/8 * y;
    buf += x/8;
    if(lv_color_brightness(color) < 128) {
    //if (*p == LV_COLOR_BLACK) {
      (*buf) &= ~(1 << (7 - x % 8));
    } else {
      (*buf) |= (1 << (7 - x % 8));
    }
}

////////////////////////////////////////////////////////////////////////////////
void hw_init(void)
{
#if defined(ARDUINO)
    Serial.begin(115200);
    // Wait for USB Serial.
    while (!Serial) {}
    delay(200);
    // Read any input
    while (Serial.read() >= 0) {}
#endif
    setup_rotary();

    /* Add a display
     * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    static lv_disp_buf_t disp_buf;
    static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 8 / 8];                     /*Declare a buffer for 10 lines*/
    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 8 / 8);    /*Initialize the display buffer*/

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.flush_cb = cb_flush_adagfx; /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
    //disp_drv.set_px_cb = cb_set_px_adagfx;
    //disp_drv.rounder_cb = cb_rounder_adagfx;

    disp_drv.buffer = &disp_buf;
    //disp_drv.disp_fill = monitor_fill;      /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
    //disp_drv.disp_map = monitor_map;        /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
    lv_disp_drv_register(&disp_drv);

    /* Add the rotary encoder as input device */
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = rotary_encoder_lv_read;
    lv_indev_t* encoder_indev = lv_indev_drv_register(&indev_drv);
    rotary_group_init(encoder_indev);

    /* Tick init.
     * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about how much time were elapsed
     * Create an SDL thread to do this*/
}

static int pre_lvtick = 0;
static int pre_disp = 0;

void hw_loop(void)
{
    int cur;
    loop_rotary();
    cur = millis();
    if (pre_lvtick + 5 < cur) {
        pre_lvtick = cur;
        lv_tick_inc(5);
        lv_task_handler();
    }
    if (pre_disp + 50 < cur) {
        pre_disp = cur;
        display.display();
    }
}

