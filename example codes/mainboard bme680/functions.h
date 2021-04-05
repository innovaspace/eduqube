//-----------------------------------------------------------------------------
//  functions.h
//  Mainboard BME680
//
//  functions used in functions.cpp. Can be called from anywhere
//  Global array and global variable, defined in functions.cpp
//  data structure with variables to be transmitted
//-----------------------------------------------------------------------------

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct dataStruct
{
    float h, p, t, a, g, ax, ay, az, gx, gy, gz, mgx, mgy, mgz, g_lat, g_lng, voltage, power, current;
};

extern byte zize;
extern byte tx_buf[sizeof(dataStruct)];

void reset_wtd (void);
void get_data();
void print_data();
void blink_red();
void blink_green();
void blink_blue_2();
void startup();

#endif
