/*
  GPS program. Communication with UBLOX NEO-7M is initialized, latitude and longitude are obtained
*/

#include <TinyGPS++.h>
#include "gps.h"
#include "config.h"
#include "functions.h"

TinyGPSPlus gps;

extern struct dataStruct myData;                        //The sctuctured variable is declared as external

boolean gpsstatus = 1;
void gps_setup()
{
  Serial1.begin(GPSBaud);                               //UART comunication with the GPS module is started by Serial1
}

void read_gps()                                         //If the communication is set correctly, gps data is read
{
  while (Serial1.available() > 0)
    if (gps.encode(Serial1.read()))
    {
      if (gps.location.isValid())
      {
        myData.g_lat = gps.location.lat();                //Latitude is obtained and stored on the scructured variable
        myData.g_lng = gps.location.lng();                //Longitude is obtained and stored on the scructured variable
      }
    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No se detecto un GPS"));          //A message is printed in the serial monotor if there is no response after 5 seconds
    gpsstatus = 0;
  }
}
