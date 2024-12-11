#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>


/**
 * Recommended board settings for platformio.ini file
 * 
 * board = esp32-s3-devkitc-1
 * board_build.partitions = max_app_8MB.csv
 * 
 */

#define WIDTH 320
#define HEIGHT 480

class LGFX : public lgfx::LGFX_Device
{

    lgfx::Panel_ILI9488 _panel_instance;

    lgfx::Bus_Parallel16 _bus_instance;

    lgfx::Light_PWM _light_instance;

    lgfx::Touch_FT5x06 _touch_instance;

public:
    LGFX(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.port = 0;
            cfg.freq_write = 40000000;
            cfg.pin_wr = 18;  // pin number connecting WR
            cfg.pin_rd = 48;  // pin number connecting RD
            cfg.pin_rs = 45;  // Pin number connecting RS(D/C)
            cfg.pin_d0 = 47;  // pin number connecting D0
            cfg.pin_d1 = 21;  // pin number connecting D1
            cfg.pin_d2 = 14;  // pin number connecting D2
            cfg.pin_d3 = 13;  // pin number connecting D3
            cfg.pin_d4 = 12;  // pin number connecting D4
            cfg.pin_d5 = 11;  // pin number connecting D5
            cfg.pin_d6 = 10;  // pin number connecting D6
            cfg.pin_d7 = 9;   // pin number connecting D7
            cfg.pin_d8 = 3;   // pin number connecting D8
            cfg.pin_d9 = 8;   // pin number connecting D9
            cfg.pin_d10 = 16; // pin number connecting D10
            cfg.pin_d11 = 15; // pin number connecting D11
            cfg.pin_d12 = 7;  // pin number connecting D12
            cfg.pin_d13 = 6;  // pin number connecting D13
            cfg.pin_d14 = 5;  // pin number connecting D14
            cfg.pin_d15 = 4;  // pin number connecting D15

            _bus_instance.config(cfg);              // Apply the settings to the bus.
            _panel_instance.setBus(&_bus_instance); // Sets the bus to the panel.
        }

        {                                        // Set display panel control.
            auto cfg = _panel_instance.config(); // Get the structure for display panel settings.

            cfg.pin_cs = -1;   // Pin number to which CS is connected (-1 = disable)
            cfg.pin_rst = -1;  // pin number where RST is connected (-1 = disable)
            cfg.pin_busy = -1; // pin number to which BUSY is connected (-1 = disable)

            // * The following setting values ​​are set to general default values ​​for each panel, and the pin number (-1 = disable) to which BUSY is connected, so please try commenting out any unknown items.

            cfg.memory_width = 320;  // Maximum width supported by driver IC
            cfg.memory_height = 480; // Maximum height supported by driver IC
            cfg.panel_width = 320;   // actual displayable width
            cfg.panel_height = 480;  // actual displayable height
            cfg.offset_x = 0;        // Panel offset in X direction
            cfg.offset_y = 0;        // Panel offset in Y directioncfg.offset_rotation = 2;
            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits = 1;
            cfg.readable = false;
            cfg.invert = false;
            cfg.rgb_order = false;
            cfg.dlen_16bit = true;
            cfg.bus_shared = true;

            _panel_instance.config(cfg);
        }
        {                                        // Set backlight control. (delete if not necessary)
            auto cfg = _light_instance.config(); // Get the structure for backlight configuration.

            cfg.pin_bl = 46;     // pin number to which the backlight is connected
            cfg.invert = false;  // true to invert backlight brightness
            cfg.freq = 44100;    // backlight PWM frequency
            cfg.pwm_channel = 0; // PWM channel number to use

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance); // Sets the backlight to the panel.
        }

        { // Configure settings for touch screen control. (delete if not necessary)
          auto cfg = _touch_instance.config();

          cfg.x_min = 0;   // Minimum X value (raw value) obtained from the touchscreen
          cfg.x_max = 319; // Maximum X value (raw value) obtained from the touchscreen
          cfg.y_min = 0;   // Minimum Y value obtained from touchscreen (raw value)
          cfg.y_max = 479; // Maximum Y value (raw value) obtained from the touchscreen
          cfg.pin_int = -1; // pin number to which INT is connected
          cfg.bus_shared = true;
          cfg.offset_rotation = 0;

          // For I2C connection
          cfg.i2c_port = 0;    // Select I2C to use (0 or 1)
          cfg.i2c_addr = 0x38; // I2C device address number
          cfg.pin_sda = 38;     // pin number where SDA is connected
          cfg.pin_scl = 39;     // pin number to which SCL is connected
          cfg.freq = 400000;   // set I2C clock

          _touch_instance.config(cfg);
          _panel_instance.setTouch(&_touch_instance); // Set the touchscreen to the panel.
        }

        setPanel(&_panel_instance); // Sets the panel to use.
    }
};

LGFX tft;
