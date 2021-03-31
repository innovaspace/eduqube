/*
  All the functions used in functions.cpp are declared, so they can be called from anywhere
  A global array and variable are declared, later defined in functions.cpp
  The data structure with all the variables to be transmitted is daclared
*/

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
