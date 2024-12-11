
#include "app_hal.h"
#include "lvgl.h"


/* include only one display settings */
// #include "displays/lgfx_wt32sc01_plus.hpp"
#include "displays/lgfx_elecrow_3_5.hpp"


static const uint32_t screenWidth = WIDTH;
static const uint32_t screenHeight = HEIGHT;

const unsigned int lvBufferSize = screenWidth * 30;
uint8_t lvBuffer[2][lvBufferSize];

static lv_display_t *lvDisplay;
static lv_indev_t *lvInput;

#if LV_USE_LOG != 0
static void lv_log_print_g_cb(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  LV_UNUSED(buf);
}
#endif

/* Display flushing */
void my_disp_flush(lv_display_t *display, const lv_area_t *area, unsigned char *data)
{

  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);
  lv_draw_sw_rgb565_swap(data, w * h);

  if (tft.getStartCount() == 0)
  {
    tft.endWrite();
  }
  tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t *)data);
  lv_display_flush_ready(display); /* tell lvgl that flushing is done */
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;
  bool touched = tft.getTouch(&touchX, &touchY);
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;
    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

/* Tick source, tell LVGL how much time (milliseconds) has passed */
static uint32_t my_tick(void)
{
  return millis();
}

void hal_setup(void)
{

  /* Initialize the display drivers */
  tft.init();
  tft.initDMA();
  tft.startWrite();
  tft.fillScreen(TFT_BLACK);

  /* Set display rotation to landscape */
  // tft.setRotation(1);

  /* Set the tick callback */
  lv_tick_set_cb(my_tick);

  /* Create LVGL display and set the flush function */
  lvDisplay = lv_display_create(screenWidth, screenHeight);
  lv_display_set_color_format(lvDisplay, LV_COLOR_FORMAT_RGB565);
  lv_display_set_flush_cb(lvDisplay, my_disp_flush);
  lv_display_set_buffers(lvDisplay, lvBuffer[0], lvBuffer[1], lvBufferSize, LV_DISPLAY_RENDER_MODE_PARTIAL);

  /* Set the touch input function */
  lvInput = lv_indev_create();
  lv_indev_set_type(lvInput, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(lvInput, my_touchpad_read);
}

void hal_loop(void)
{
  /* NO while loop in this function! (handled by framework) */
  lv_timer_handler(); // Update the UI-
  delay(5);
}
