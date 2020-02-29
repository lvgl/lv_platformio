/**
 * \file    config-hw.h
 * \brief   Config of hardware
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-01-05
 * \copyright GPL/BSD
 */
#ifndef _CONFIG_HW_GDTEST_H
#define _CONFIG_HW_GDTEST_H 1

/**
   specials pins are required for interrupts
   Board:                                    int.0  int.1  int.2  int.3  int.4  int.5            Level
   Uno, Mini, Pro, ATmega168, ATmega328..... 2      3      x       x      x     x                5v
   Mega2560................................. 2      3      21      20     19    18               5v
   Leonardo, Micro, ATmega32U4.............. 3      2      0       1      7     x                5v
   Digistump, Trinket, ATtiny85............. 2/physical pin 7                                    5v
   Due, SAM3X8E............................. all digital pins                                    3v
   Zero, ATSAMD21G18........................ all digital pins, except pin 4                      3v
   Blue Pill, STM32F103xxxx boards.......... all digital pins, maximun 16 pins at the same time  3v
   ESP8266.................................. all digital pins, except gpio6 - gpio11 & gpio16    3v/5v
   ESP32.................................... all digital pins                                    3v

   specials pins are required for I2C bus
   Board:                                    SDA                    SCL                    Level
   Uno, Mini, Pro, ATmega168, ATmega328..... A4                     A5                     5v
   Mega2560................................. 20                     21                     5v
   Due, SAM3X8E............................. 20                     21                     3.3v
   Leonardo, Micro, ATmega32U4.............. 2                      3                      5v
   Digistump, Trinket, ATtiny85............. 0/physical pin no.5    2/physical pin no.7    5v
   Blue Pill, STM32F103xxxx boards.......... PB7                    PB6                    3.3v/5v
   ESP8266 ESP-01........................... GPIO0/D5               GPIO2/D3               3.3v/5v
   NodeMCU 1.0, WeMos D1 Mini............... GPIO4/D2               GPIO5/D1               3.3v/5v
   ESP32.................................... GPIO21/D21             GPIO22/D22             3.3v

   NOTE:
   - LOW     interrupt trigges whenever the pin is low
   - HIGH    interrupt triggers whenever the pin is high (Arduino Due, Zero, MKR1000 only)
   - CHANGE  interrupt triggers whenever the pin changes value
   - RISING  interrupt triggers when the pin goes from low to high
   - FALLING interrupt triggers when the pin goes from high to low
 */

////////////////////////////////////////////////////////////////////////////////

#define PIN_SENSOR_DHT  D1     // what pin we're connected to

#if defined(ARDUINO_ARCH_ESP8266)
// ESP8266
#define PIN_ADC        A0
#define PIN_ROTARY_BTN D6
#define PIN_ROTARY_A   D5
#define PIN_ROTARY_B   D7

#define I2C_SDA D2 // use esp8266 arduino PIN_WIRE_SDA(IO4)
#define I2C_SCL D1 // use esp8266 arduino PIN_WIRE_SCL(IO5)
#define OLED_RESET    -1

// ILI9341 display module
#define PIN_LCD_TFT_MISO D6 // GPIO12
#define PIN_LCD_TFT_MOSI D7 // GPIO13
#define PIN_LCD_TFT_SCK  D5 // GPIO14
#define PIN_LCD_TFT_CS   D8 // GPIO15 (option=-1) Chip select pin
#define PIN_LCD_TFT_DC   D4 // GPIO2 (required) Data/Command pin
#define PIN_LCD_TFT_RESET -1 //D0 // (option=-1)
#define PIN_LCD_TFT_BACKLIGHT -1 // backlight led
#define PIN_LCD_SD_MISO PIN_LCD_TFT_MISO
#define PIN_LCD_SD_MOSI PIN_LCD_TFT_MOSI
#define PIN_LCD_SD_SCK  PIN_LCD_TFT_SCK
#define PIN_LCD_SD_CS   -1
#define PIN_LCD_T_MISO  PIN_LCD_TFT_MISO
#define PIN_LCD_T_MOSI  PIN_LCD_TFT_MOSI
#define PIN_LCD_T_SCK   PIN_LCD_TFT_SCK
#define PIN_LCD_T_CS    -1
#define PIN_LCD_T_IRQ   -1

// NEO-6M GPS Module
#define PIN_GPS_PPS D3
#define PIN_GPS_RX  D9  // U0RX
#define PIN_GPS_TX  D10 // U0TX

// LoRa 915M SX1276 Module
#define PIN_RFM_MISO    D6
#define PIN_RFM_MOSI    D7
#define PIN_RFM_SCK     D5
#define PIN_RFM_NSS     D4
#define PIN_RFM_DIO_IRQ D8
#define PIN_RFM_RESET   D0

#elif defined(ARDUINO_ARCH_ESP32)
// ESP32
#define USE_ESP32_HELTEC_LORA2 0 //1

#if USE_ESP32_HELTEC_LORA2
#define PIN_ADC        39

// Rotary Encoder device
#define PIN_ROTARY_BTN 0
#define PIN_ROTARY_A   32
#define PIN_ROTARY_B   33

#define I2C_SDA 4 // heltec WIFI LoRa 32(V2)
#define I2C_SCL 15 // heltec WIFI LoRa 32(V2)
#define OLED_RESET    16

#else
#define PIN_ADC        33

// Rotary Encoder device
#define PIN_ROTARY_BTN 0
#define PIN_ROTARY_A   25
#define PIN_ROTARY_B   26

#define I2C_SDA 21 // ESP32 Battery Module
#define I2C_SCL 22 // ESP32 Battery Module
#define OLED_RESET    -1
#endif

// ILI9341 display module
#define PIN_LCD_TFT_MISO  12
#define PIN_LCD_TFT_MOSI  13
#define PIN_LCD_TFT_SCK   14
#define PIN_LCD_TFT_CS    15 // (option=-1) Chip select pin
#define PIN_LCD_TFT_DC     2 // (required) Data/Command pin
#define PIN_LCD_TFT_RESET -1 // (option=-1)
#define PIN_LCD_SD_MISO   PIN_LCD_TFT_MISO
#define PIN_LCD_SD_MOSI   PIN_LCD_TFT_MOSI
#define PIN_LCD_SD_SCK    PIN_LCD_TFT_SCK
#define PIN_LCD_SD_CS     27
#define PIN_LCD_T_MISO    PIN_LCD_TFT_MISO
#define PIN_LCD_T_MOSI    PIN_LCD_TFT_MOSI
#define PIN_LCD_T_SCK     PIN_LCD_TFT_SCK
#define PIN_LCD_T_CS       0
#define PIN_LCD_T_IRQ     33

// NEO-6M GPS Module
#define PIN_GPS_PPS 32
#define PIN_GPS_RX  16 // U2RX
#define PIN_GPS_TX  17 // U0TX

// LoRa 915M SX1276 Module
#define PIN_RFM_MISO    19
#define PIN_RFM_MOSI    23
#define PIN_RFM_SCK     18
#define PIN_RFM_NSS      5
#define PIN_RFM_DIO_IRQ  4
#define PIN_RFM_RESET   -1

#elif defined (__STM32F1__) // defined(STM32_MCU_SERIES)
// mapple mini: scl(16), sda(15)
// MAPLEMINI

#elif defined(__AVR_ATmega2560__)
// 2560, 12864 LCD, RepRapDiscount FULL GRAPHIC Smart Controller
#define PIN_ROTARY_BTN 35
#define PIN_ROTARY_A   31
#define PIN_ROTARY_B   33

/*
#define LCD_PINS_RS     16
#define LCD_PINS_ENABLE 17
#define LCD_PINS_D4     23
#define LCD_PINS_D5     25
#define LCD_PINS_D6     27
#define LCD_PINS_D7       29
#define ST7920_CLK_PIN  LCD_PINS_D4
#define ST7920_DAT_PIN  LCD_PINS_ENABLE
#define ST7920_CS_PIN   LCD_PINS_RS
*/
#define PIN_LCD_RS 16 // ST7920_CS
#define PIN_LCD_RW -1
#define PIN_LCD_EN 17 // ST7920_DAT/MOSI
#define PIN_LCD_D4 23 // ST7920_CLK
#define PIN_LCD_D5 25
#define PIN_LCD_D6 27
#define PIN_LCD_D7 29

// Graphical LCD
#define PIN_GLCD_CS   PIN_LCD_RS
#define PIN_GLCD_MOSI PIN_LCD_EN
#define PIN_GLCD_CLK  PIN_LCD_D4


#define PIN_ADC        A3

#define I2C_SDA 20
#define I2C_SCL 21
#define OLED_RESET    -1

#else
// Arduino Uno
// __AVR_ATmega328P__, __AVR_ATmega32U4__
#define PIN_LCD_RS  8
#define PIN_LCD_RW 12
#define PIN_LCD_EN 13
#define PIN_LCD_D4  4
#define PIN_LCD_D5  5
#define PIN_LCD_D6  6
#define PIN_LCD_D7  7

#define PIN_RGBLED_R  9
#define PIN_RGBLED_B 10
#define PIN_RGBLED_G 11

#define PIN_ROTARY_BTN A0
#define PIN_ROTARY_A   A1
#define PIN_ROTARY_B   A2

#define PIN_ADC        A3

#define I2C_SDA A4
#define I2C_SCL A5
#define OLED_RESET    -1

#endif

////////////////////////////////////////////////////////////////////////////////

// the number of character of the LiquidCrystal character display
#define LCD_COL 16
#define LCD_ROW  2

#ifndef USE_LIQLCD
#  define USE_LIQLCD 1
#  ifndef __AVR_ATmega328P__
#    undef  USE_LIQLCD
#    define USE_LIQLCD 0
#  endif
#endif

#ifndef USE_ILI9341
#if defined(ARDUINO)
#define USE_ILI9341 1
#else
#define USE_ILI9341 0
#endif
#endif

#ifndef USE_ST7920
#if defined(ARDUINO)
#define USE_ST7920 1
#else
#define USE_ST7920 0
#endif
#endif

#ifndef USE_EMBGFX
#  define USE_EMBGFX 1
#  ifndef __AVR_ATmega328P__
#    undef  USE_EMBGFX
#    define USE_EMBGFX 0
#  endif
#endif

#ifndef USE_ADAGFX
#if defined(ARDUINO)
#define USE_ADAGFX 1
#else
#define USE_ADAGFX 0
#endif
#endif

#ifndef USE_LCDGFX
#if defined(ARDUINO)
#define USE_LCDGFX 1
#else
#define USE_LCDGFX 0
#endif
#endif

#ifndef USE_TFTESPI
#if defined(ARDUINO)
#define USE_TFTESPI 1
#else
#define USE_TFTESPI 0
#endif
#endif


#define USE_ROTARY 1
#if ! defined(ARDUINO)
#undef USE_ROTARY
#define USE_ROTARY 0
#endif


#ifdef __AVR__
#define USE_STDMAP 0
#else
#define USE_STDMAP 1
#endif

#endif // _CONFIG_HW_GDTEST_H
