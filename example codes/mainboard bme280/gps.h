  
//-----------------------------------------------------------------------------
//  gps.h
//  Mainboard BME280
//  Functions to be used in "gps.cpp". Can be called from "main.cpp"
//-----------------------------------------------------------------------------

#ifndef GPS_H
#define GPS_H

extern boolean gpsstatus;

void gps_setup();
void read_gps();
#endif
