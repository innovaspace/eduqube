//-----------------------------------------------------------------------------
//  config.h
//  Ground Station
//  General configuration file
//-----------------------------------------------------------------------------

#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------------------------------------
//  LoRa
//-----------------------------------------------------------------------------
#define TX_POWER 20         // Transmission power in dBm (range = 2-20)
#define SF 12               // Spreading Factor (range = 6-12)
#define RFM95_CS 18         // Pin connected to radio Chip Select
#define RFM95_INT 26        // Pin connected to radio interrupt pin
#define FREQ 915.0          // RFM95 transmission frequency

//-----------------------------------------------------------------------------
//  WiFi
//-----------------------------------------------------------------------------
#define WiFi_SSID ""        // Insert here your WiFi SSID
#define PASSWORD ""         // Insert here your WiFi password

//-----------------------------------------------------------------------------
//  EMQX MQTT
//-----------------------------------------------------------------------------
#define mqtt_server ""      // Insert here your MQTT Broker server IP

//-----------------------------------------------------------------------------
//  Launch date
//  set launch date for dashboard countdown
//-----------------------------------------------------------------------------
#define launch_date "Sep 30, 2022 00:00:00" 

#endif
