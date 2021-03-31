/*
All the fucntions to be used in "sensors.cpp" are declared, so they can be called from "main.cpp"
Sensor status variables are declared  
*/

#ifndef SENSORS_H
#define SENSORS_H

extern boolean bmestatus;
extern int mpustatus;

void sensors_setup();
void read_bme();
void read_mpu();
void read_ina();
#endif
