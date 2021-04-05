//-----------------------------------------------------------------------------
//	config.h
//	Ground Station
//	General configuration file
//-----------------------------------------------------------------------------

#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------------------------------------
// LoRa
//-----------------------------------------------------------------------------
#define TX_POWER 20         // Transmission power in dBm (Possible values = 2-20)
#define SF 12               // Spreading Factor (Possible values = 6-12)
#define RFM95_CS 18         // Pin connected to radio Chip Select
#define RFM95_INT 26        // Pin connected to radio interrupt pin
#define FREQ 915.0          // RFM95 transmission frequency

//-----------------------------------------------------------------------------
// WiFi
//-----------------------------------------------------------------------------
#define WiFi_SSID ""        // Insert WiFi SSID
#define PASSWORD ""         // Insert WiFi password

//-----------------------------------------------------------------------------
// EMQX MQTT
//-----------------------------------------------------------------------------
#define mqtt_server ""      // Insert MQTT Broker server IP

//-----------------------------------------------------------------------------
// Launch date
//-----------------------------------------------------------------------------
#define launch_date "Sep 30, 2022 00:00:00" // set launch date for dashboard countdown

#endif
