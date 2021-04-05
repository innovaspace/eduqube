//-----------------------------------------------------------------------------
//  display.h
//  Ground Station
//
//  Declare Functions used in "wifi_c.cpp" to be called from other files
//
//	The OLED instance is declared as external, to allow printing in OLED screen
//  from every file that includes "display.h"
//-----------------------------------------------------------------------------

#ifndef DISPLAY_H
#define DISPLAY_H

#include <OLED_I2C.h>   	// OLED I2C library

extern OLED myOLED;     	// instance of the OLED class

void oled_setup();
void print_status();

#endif
