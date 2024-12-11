#pragma once

#include "PanelLan.h"


/**
 * Recommended board settings for platformio.ini file
 * 
 * board = esp32-s3-devkitm-1
 * 
 */

#define WIDTH 320
#define HEIGHT 480


/* Set the board type. (Uses LovyanGFX internally to manage display drivers) */
PanelLan tft(BOARD_SC01_PLUS);

