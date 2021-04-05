//-----------------------------------------------------------------------------
//  upload.cpp
//  Ground Station
//-----------------------------------------------------------------------------

#include <Arduino.h>
#include "upload.h"
#include "mqtt.h"
#include "functions.h"
#include "radio.h"
#include "config.h"

extern struct dataStruct myData; // The sctuctured variable is declared as external

//-----------------------------------------------------------------------------
//  VARIABLES
//-----------------------------------------------------------------------------
long lastMsg = 0;
float diff = 1.0;
float diff2 = 0.1;

float hum = 0.0;
float pres = 0.0;
float temp = 0.0;
float alt = 0.0;
float accelX = 0.0;
float accelY = 0.0;
float accelZ = 0.0;
float gyroX = 0.0;
float gyroY = 0.0;
float gyroZ = 0.0;
float magX = 0.0;
float magY = 0.0;
float magZ = 0.0;
float lat = 0.0;
float lon = 0.0;
float rssi = 0.0;
//-----------------------------------------------------------------------------
//  Checkbound
//  Checks if the input value changed above the trigger level
//-----------------------------------------------------------------------------
bool checkBound(float newValue, float prevValue, float maxDiff)
{
    return newValue < prevValue - maxDiff || newValue > prevValue + maxDiff;
}
//-----------------------------------------------------------------------------
//  Upload Data
//  uploads the data to the mqtt server every 5 seconds if changed its value
//-----------------------------------------------------------------------------
void upload_data()
{
  long now = millis();
  if (now - lastMsg > 5000) {
      // Wait a few seconds between measurements
      lastMsg = now;
      if (checkBound(myData.h, hum, diff)) {                        // If the humidity value changed its value by 1 or more 
          hum = myData.h;                                           // The new value is stored in "hum"
          client.publish(humidity_topic, String(hum).c_str(),true); // The new value is published as a string in the topic "humidity_topic" with the flag "true", so it is retained on the server 
      }

      if (checkBound(myData.p, pres, diff)) {
          pres = myData.p;
          client.publish(pressure_topic, String(pres).c_str(),true);
      }

      if (checkBound(myData.t, temp, diff)) {
          temp = myData.t;
          client.publish(temperature_topic, String(temp).c_str(),true);
      }

      if (checkBound(myData.a, alt, diff)) {
          alt = myData.a;
          client.publish(altitude_topic, String(alt).c_str(),true);
      }

      if (checkBound(myData.ax, accelX, diff)) {
          accelX = myData.ax;
          client.publish(accelerometer_x_axis_topic, String(accelX).c_str(),true);
      }

      if (checkBound(myData.ay, accelY, diff)) {
          accelY = myData.ay;
          client.publish(accelerometer_y_axis_topic, String(accelY).c_str(),true);
      }

      if (checkBound(myData.az, accelZ, diff)) {
          accelZ = myData.az;
          client.publish(accelerometer_z_axis_topic, String(accelZ).c_str(),true);
      }

      if (checkBound(myData.gx, gyroX, diff)) {
          gyroX = myData.gx;
          client.publish(gyroscope_x_axis_topic, String(gyroX).c_str(),true);
      }

      if (checkBound(myData.gy, gyroY, diff)) {
          gyroY = myData.gy;
          client.publish(gyroscope_y_axis_topic, String(gyroY).c_str(),true);
      }

      if (checkBound(myData.gz, gyroZ, diff)) {
          gyroZ = myData.gz;
          client.publish(gyroscope_z_axis_topic, String(gyroZ).c_str(),true);
      }

      if (checkBound(myData.mgx, magX, diff)) {
          magX = myData.mgx;
          client.publish(magnetometer_x_axis_topic, String(magX).c_str(),true);
      }

      if (checkBound(myData.mgy, magY, diff)) {
          magY = myData.mgy;
          client.publish(magnetometer_y_axis_topic, String(magY).c_str(),true);
      }

      if (checkBound(myData.mgz, magZ, diff)) {
          magZ = myData.mgz;
          client.publish(magnetometer_z_axis_topic, String(magZ).c_str(),true);
      }

      if (checkBound(myData.g_lat, lat, diff)) {
          lat = myData.g_lat;
          client.publish(gps_latitude_topic, String(lat).c_str(),true);
      }

      if (checkBound(myData.g_lng, lon, diff)) {
          lon = myData.g_lng;
          client.publish(gps_longitude_topic, String(lon).c_str(),true);
      }

      if (checkBound(myData.rssi, lon, diff)) {
          rssi = myData.rssi;
          client.publish(rssi_topic, String(rssi).c_str(),true);
      }
  }
}
