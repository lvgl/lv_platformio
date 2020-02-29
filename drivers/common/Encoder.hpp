/**
 * \file    Encoder.hpp
 * \brief   Rotary Encoder
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-02-13
 * \copyright GPL/BSD
 */
#ifndef _ROTARY_ENCODER_H
#define _ROTARY_ENCODER_H

#if USE_ROTARY
#include "RotaryButton.h"

////////////////////////////////////////////////////////////////////////////////

class Encoder {
public:
  Encoder(int pin_a, int pin_b, int pin_btn) : r(pin_a, pin_b), b(pin_btn), diff(0), btn(0) {}

  void add_diff(int df) { diff += df; }
  int get_diff() {
    int ret = diff;
    diff = 0;
    return ret;
  }
  // btn: 0 - none, 1 - click, 2 - double, 3 - triple, 4 -- long
  void set_btn(int bt) { btn = bt; }
  int get_btn() {
    int ret = btn;
    btn = 0;
    return ret;
  }
  int isPressed() { return b.isPressed(); }

  void begin() {
    r.setHandler(this, cb_rotary_position);
    b.setHandler(this, cb_button_pressed);
    r.begin();
    b.begin();
  }

  void loopOnce() {
    r.loopOnce();
    b.loopOnce();
  }

private:
  Rotary r;
  Button b;
  int diff;
  int btn;

  static void cb_rotary_position(void * user_data, Rotary::Direction change_type, int offset) {
    Encoder *pe = (Encoder *)user_data;

    switch (change_type) {
    case Rotary::Direction::Left:
      Serial.print("Rotary Left:   "); Serial.println(offset);
      pe->add_diff(offset);
      break;
    case Rotary::Direction::Right:
      Serial.print("Rotary Right:  "); Serial.println(offset);
      pe->add_diff(offset);
      break;
    default:
      Serial.print("Rotary (None): "); Serial.println(offset);
      break;
    }
  }

  static void cb_button_pressed (void * user_data, Button::PressEvent type)
  {
    Encoder *pe = (Encoder *)user_data;
    switch(type) {
    case Button::PressEvent::None:
      //Serial.println("Button: None");
      break;
    case Button::PressEvent::Changed:
      //Serial.println("Button: Changed");
      break;
    case Button::PressEvent::Pressed:
      Serial.println("Button: Pressed");
      break;
    case Button::PressEvent::Long:
    {
      pe->set_btn(4);
      Serial.println("Button: Long (Reset)");
    }
      break;
    case Button::PressEvent::Released:
      Serial.println("Button: Released");
      break;
    case Button::PressEvent::Click:
      pe->set_btn(1);
      Serial.println("Button: Click (Enter)");
      break;
    case Button::PressEvent::Tap:
      //Serial.println("Button: Tap");
      break;
    case Button::PressEvent::Double:
      pe->set_btn(2);
      Serial.println("Button: Double (Quit)");
      break;
    case Button::PressEvent::Triple:
      pe->set_btn(3);
      Serial.println("Button: Triple (Easter eggs)");
      break;
    default:
      Serial.println("Button: Error State");
      break;
    }
  }

};
#endif // USE_ROTARY

#endif // _ROTARY_ENCODER_H

//static Encoder e = Encoder(PIN_ROTARY_A, PIN_ROTARY_B, PIN_ROTARY_BTN);
//    e.loopOnce();

