//-----------------------------------------------------------------------------
//  gps.cpp
//  Mainboard BME680
// 
//  GPS program. 
//  Init communication with UBLOX NEO-7M
//  latitude and longitude are obtained
//-----------------------------------------------------------------------------

#include <TinyGPS++.h>
#include "gps.h"
#include "config.h"
#include "functions.h"

TinyGPSPlus gps;

// The sctuctured variable is declared as external
extern struct dataStruct myData;                        

boolean gpsstatus = 1;
//-----------------------------------------------------------------------------
//  GPS Setup
//  Start UART comunication with GPS module
//-----------------------------------------------------------------------------
void gps_setup()
{
    Serial1.begin(GPSBaud);
}
//-----------------------------------------------------------------------------
//  Read GPS
//  If communication is set correctly, read gps data
//-----------------------------------------------------------------------------
void read_gps()
{
    while (Serial1.available() > 0)
        if (gps.encode(Serial1.read()))
        {
            if (gps.location.isValid())
            {
                myData.g_lat = gps.location.lat();  // get LAT and store in data scruct
                myData.g_lng = gps.location.lng();  // get LON and store in data scruct
            }
        }

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        // Print message if there is no reply after 5 seconds
        Serial.println(F("No se detecto un GPS"));          
        gpsstatus = 0;
    }
}
