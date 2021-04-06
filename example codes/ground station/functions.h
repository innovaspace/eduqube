//-----------------------------------------------------------------------------
//  functions.h
//  Ground Station
// 	Define data structure to store recieved data
//-----------------------------------------------------------------------------

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct dataStruct
{
    float h, p , t, a, g, ax, ay, az, gx, gy, gz, mgx, mgy, mgz, g_lat, g_lng, voltage, power, current, rssi;
};

void print_data();

#endif
