//-----------------------------------------------------------------------------
//  radio.h
//  Ground Station
//	All the fucntions to be used in "radio.cpp" are declared, so they can be called from "main.cpp"
//	rf95 object is declared globally
//-----------------------------------------------------------------------------

#ifndef RADIO_H
#define RADIO_H

#include <RH_RF95.h>

extern RH_RF95 rf95;

void radio_setup();
void radio_loop();

#endif
