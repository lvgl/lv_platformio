#ifndef DRIVER_H
#define DRIVER_H

#include "lvdrv-rotarygrp.h"

#ifdef __cplusplus
extern "C" {
#endif

void hw_init(void);
void hw_loop(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DRIVER_H*/
