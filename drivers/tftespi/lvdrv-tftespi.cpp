/**
 * \file    lvdrv-tftespi.cpp
 * \brief   TFT eSPI driver for LittlevGL
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-02-03
 * \copyright GPL/BSD
 */

//#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#include "lvgl.h"
#include "lvdrv-tftespi.h"
#include "setuprotary.h"
#include "lvdrv-rotarygrp.h"

////////////////////////////////////////////////////////////////////////////////
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

/**
 * Flush a buffer to the marked area
 * @param drv pointer to driver where this function belongs
 * @param area an area where to copy `color_p`
 * @param color_p an array of pixel to copy to the `area` part of the screen
 */
void tft_espi_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    uint16_t c;

    tft.startWrite(); /* Start new TFT transaction */
    tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1),
                      (area->y2 - area->y1 + 1)); /* set the working window */
    for(int y = area->y1; y <= area->y2; y++) {
        for(int x = area->x1; x <= area->x2; x++) {
            c = color_p->full;
            tft.writeColor(c, 1);
            color_p++;
        }
    }
    tft.endWrite(); /* terminate TFT transaction */

    lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
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
    tft.begin(); /* TFT init */
#ifndef TFT_ROTATION
#define TFT_ROTATION 1
#endif
    tft.setRotation(TFT_ROTATION); /* Landscape orientation */

#if defined(ARDUINO_ARCH_ESP32)
    /* allocate on iram (or psram ?) */
    int buffer_size                      = 1024 * 8;
    static lv_color_t * guiVdbBuffer = (lv_color_t *)malloc(sizeof(lv_color_t) * buffer_size);
    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, guiVdbBuffer, NULL, buffer_size);
#else
    /* allocate on heap */
    static lv_color_t guiVdbBuffer[1024 * 4];
    int buffer_size = sizeof(guiVdbBuffer) / sizeof(guiVdbBuffer[0]);
    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, guiVdbBuffer, NULL, buffer_size);
#endif

    /* Initialize PNG decoder */
    // png_decoder_init();

    /* Initialize the display driver */
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    //disp_drv.hor_res = LV_HOR_RES_MAX;
    //disp_drv.ver_res = LV_VER_RES_MAX;
    disp_drv.flush_cb = tft_espi_flush;
    disp_drv.buffer   = &disp_buf;
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
        //tft.display();
    }
}

