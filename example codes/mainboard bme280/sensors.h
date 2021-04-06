//-----------------------------------------------------------------------------
//  sensors.h
//  Mainboard BME680
//  Functions to be used in "sensors.cpp". Can be called from "main.cpp"
//  Sensor status variables
//-----------------------------------------------------------------------------

#ifndef SENSORS_H
#define SENSORS_H

extern boolean bmestatus;
extern int mpustatus;

void sensors_setup();
void read_bme();
void read_mpu();
void read_ina();

#endif
