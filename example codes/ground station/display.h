/*
  Functions used in "wifi_c.cpp" are declared, so they can be called from other files
  The OLED instance is declared as external, allowing to print on the OLED screen from every file that includes "display.h"
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <OLED_I2C.h>   //The OLED I2C library is included
extern OLED myOLED;     //The instance of the OLED class is declared
void oled_setup();
void print_status();
#endif
