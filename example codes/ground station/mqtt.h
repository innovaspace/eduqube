//-----------------------------------------------------------------------------
//  mqtt.h
//  Ground Station
//-----------------------------------------------------------------------------

#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>

// Define name of the topics to be used to send each data

#define humidity_topic "humidity"
#define pressure_topic "pressure"
#define temperature_topic "temperature"
#define altitude_topic "altitude"
#define accelerometer_x_axis_topic "accel_x"
#define accelerometer_y_axis_topic "accel_y"
#define accelerometer_z_axis_topic "accel_z"
#define gyroscope_x_axis_topic "gyro_x"
#define gyroscope_y_axis_topic "gyro_y"
#define gyroscope_z_axis_topic "gyro_z"
#define magnetometer_x_axis_topic "mag_x"
#define magnetometer_y_axis_topic "mag_y"
#define magnetometer_z_axis_topic "mag_z"
#define gps_latitude_topic "gps_lat"
#define gps_longitude_topic "gps_long"
#define rssi_topic "rssi"
#define launchdate_topic "launchdate"

extern PubSubClient client;

void mqttConnect();
void mqtt_loop();

#endif
