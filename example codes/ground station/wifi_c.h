//-----------------------------------------------------------------------------
//  wifi_c.h
//  Ground Station
//  Functions used in "wifi_c.cpp" are declared, so they can be called from "main.cpp"
//  "wifiClient" is declared globally, so it can be used in "mqtt.cpp"
//-----------------------------------------------------------------------------

#ifndef WIFI_C_H
#define WIFI_C_H

#include <WiFi.h>

void wifi_setup();

extern WiFiClient wifiClient;

#endif
