/**
 * \file    setuprotary.h
 * \brief   setup function for Rotary
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-01-05
 * \copyright GPL/BSD
 */

////////////////////////////////////////////////////////////////////////////////
//#include "config-hw.h"

#include "setuprotary.h"

////////////////////////////////////////////////////////////////////////////////

#if 1
#undef TD
#define TD(...)
#undef TW
#define TW(...)
#undef TE
#define TE(...)
#undef TI
#define TI(...)
#endif


#if defined(ARDUINO_ARCH_ESP8266)
// ESP8266
#define PIN_ROTARY_BTN D6
#define PIN_ROTARY_A   D5
#define PIN_ROTARY_B   D7

#elif defined(ARDUINO_ARCH_ESP32)
// ESP32
#define PIN_ROTARY_BTN 0
#define PIN_ROTARY_A   25
#define PIN_ROTARY_B   26

#elif defined(__AVR_ATmega2560__)
// 2560, 12864 LCD, RepRapDiscount FULL GRAPHIC Smart Controller
#define PIN_ROTARY_BTN 35
#define PIN_ROTARY_A   31
#define PIN_ROTARY_B   33

#elif defined(__AVR_ATmega328P__)
// Arduino Uno
#define PIN_ROTARY_BTN A0
#define PIN_ROTARY_A   A1
#define PIN_ROTARY_B   A2

#elif defined (__AVR_ATmega32U4__)
// ATMega32U4
#define PIN_ROTARY_BTN A0
#define PIN_ROTARY_A   A1
#define PIN_ROTARY_B   A2

#endif


////////////////////////////////////////////////////////////////////////////////
#if USE_ROTARY
#include "Encoder.hpp"
static Encoder e = Encoder(PIN_ROTARY_A, PIN_ROTARY_B, PIN_ROTARY_BTN);
Encoder * get_encoder() { return &e; }

#if defined(__AVR__)
#include <TimerOne.h>
void timerIsr(void) {
  e.loopOnce();
}

void setup_rotary() {
  e.begin();
  Timer1.initialize(200);
  Timer1.attachInterrupt(timerIsr);
}
#define loop_rotary_update()

#elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
// Arduino ESP default library Ticker
//#include "Ticker.h"
//Ticker rotaryTicker;
ICACHE_RAM_ATTR void timerIsr(void) {
  //noInterrupts();
  e.loopOnce();
  //interrupts();
}

#define USE_ROTARY_BUTTON_INTERRUPT 0

void setup_rotary() {
  e.begin();
  TD("setup rotary interrupts, pina=%d", PIN_ROTARY_A);
  //rotaryTicker.attach_ms(100, timerIsr);
  attachInterrupt(digitalPinToInterrupt(PIN_ROTARY_A),   timerIsr, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(PIN_ROTARY_B),   timerIsr, CHANGE);
#if USE_ROTARY_BUTTON_INTERRUPT
  attachInterrupt(digitalPinToInterrupt(PIN_ROTARY_BTN), timerIsr, CHANGE); // won't work well
#endif
}

void loop_rotary_update()
{
#if USE_ROTARY_BUTTON_INTERRUPT == 0
  static uint32_t lastService = 0;
  if (lastService + 1000 < micros()) {
    lastService = micros();
    e.loopOnce();
  }
#endif
}

#else
#include "pt.h"
#include "pttimer.h"

PT_THREAD(
rotarypt_update(struct pt_timer_pair *mpt)
)
{
  PT_BEGIN(&(mpt->pt));
  while (1)
  {
    //TD("e.service() ...");
    e.loopOnce();
    pttimer_set(&(mpt->timer), ONE_SECOND / 5);
    PT_WAIT_UNTIL(&(mpt->pt), pttimer_expired(&(mpt->timer)));
    //PT_YIELD(&(mpt->pt));
  }
  PT_END(&(mpt->pt));
}

struct pt_timer_pair rotary_pt1;

void setup_rotary() {
  TD("setup_rotary()");
  e.begin();
  pttimerpair_init(&rotary_pt1);
}

void loop_rotary_update()
{
  //TD("loop_rotary() begin");
  PT_SCHEDULE(rotarypt_update(&rotary_pt1));
  //TD("loop_rotary() end");
}

#endif

void loop_rotary() {
    loop_rotary_update();
}
#endif // USE_ROTARY


