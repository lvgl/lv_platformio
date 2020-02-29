/**
 * \file    setuprotary.h
 * \brief   setup function for Rotary
 * \author  Yunhui Fu (yhfudev@gmail.com)
 * \version 1.0
 * \date    2020-01-05
 * \copyright GPL/BSD
 */

#ifndef _SETUP_ROTARY_H
#define _SETUP_ROTARY_H 1

#ifndef USE_ROTARY
#define USE_ROTARY 1
#endif

#if USE_ROTARY
#include "Encoder.hpp"
extern Encoder * get_encoder();
void setup_rotary();
void loop_rotary();
#else
#define get_encoder()
#define setup_rotary()
#define loop_rotary()
#endif

#endif // _SETUP_ROTARY_H

