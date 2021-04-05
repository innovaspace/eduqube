//-----------------------------------------------------------------------------
//  functions.cpp
//  Ground Station
//-----------------------------------------------------------------------------

#include <Arduino.h>
#include "functions.h"

dataStruct myData;      // sctuctured variable declared as external

//-----------------------------------------------------------------------------
//  Print Data
//  Print all data stored in datastructure in serial monitor
//-----------------------------------------------------------------------------
void print_data()
{
    // BME680
    Serial.println("BME Readings:");
    Serial.print("Temperature: ");
    Serial.println(myData.t);
    Serial.print("Humidity: ");
    Serial.println(myData.h);
    Serial.print("Pressure: ");
    Serial.println(myData.p);
    Serial.print("Altitude: ");
    Serial.println(myData.a);

    // MPU9250
    Serial.println("MPU9250 Readings:");
    Serial.print("Accelerometer (X Y Z): ");
    Serial.print(myData.ax);
    Serial.print(" ");
    Serial.print(myData.ay);
    Serial.print(" ");
    Serial.println(myData.az);
    Serial.print("Gyroscope (X Y Z): ");
    Serial.print(myData.gx);
    Serial.print(" ");
    Serial.print(myData.gy);
    Serial.print(" ");
    Serial.println(myData.gz);
    Serial.print("Magnetometer (X Y Z): ");
    Serial.print(myData.mgx);
    Serial.print(" ");
    Serial.print(myData.mgy);
    Serial.print(" ");
    Serial.println(myData.mgz);

    // GPS
    Serial.println("Position");
    Serial.print("Latitude: ");
    Serial.println(myData.g_lat, 6);
    Serial.print("Longitude: ");
    Serial.println(myData.g_lng, 6);

    // NA226
    Serial.println("INA226 Readings:");
    Serial.print("Battery voltage: ");
    Serial.print(myData.voltage, 3);
    Serial.println(" V");
    Serial.print("System bus power: ");
    Serial.print(myData.power, 3);
    Serial.println(" W");
    Serial.print("System current: ");
    Serial.print(myData.current, 3);
    Serial.println(" A");
}
