/*
  Se define la estructura de datos identica a la del satélite con los datos que se van a recibir
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//A sctruture is defined to store all the recieved data
struct dataStruct
{
  float h, p , t, a, g, ax, ay, az, gx, gy, gz, mgx, mgy, mgz, g_lat, g_lng, voltage, power, current, rssi;
};

void print_data();
#endif
