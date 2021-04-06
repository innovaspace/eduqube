//-----------------------------------------------------------------------------
//  wifi_c.cpp
//  Ground Station
//  The ground station is connected to a WiFi network with the SSID and password defined in "config.h"
//  It shows the connection status on the OLED screen
//-----------------------------------------------------------------------------

#include "wifi_c.h"
#include "config.h"
#include "display.h"

WiFiClient wifiClient;

//-----------------------------------------------------------------------------
//  Wifi Setup
//-----------------------------------------------------------------------------
void wifi_setup()
{
    WiFi.disconnect();
    delay(1000);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.begin(WiFi_SSID,PASSWORD);
    delay(100);
    
    byte count = 0;

    while(WiFi.status() != WL_CONNECTED && count < 10)
    { 
        count ++;
        delay(500);
        Serial.println ("Connecting...");
        myOLED.clrScr();
        myOLED.print( "EduQube GND Station", CENTER, 0);
        myOLED.print( "Connecting to WiFi", LEFT, 16);
        myOLED.update();
    }

    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println ("Connecting...OK");
        myOLED.clrScr();
        myOLED.print( "EduQube GND Station", CENTER, 0);
        myOLED.print( "Connected to WiFi !", LEFT, 16);
        myOLED.update();
    }
    else
    {
        Serial.println ("Connecting...Failed");
        myOLED.clrScr();
        myOLED.print( "EduQube GND Station", CENTER, 0);
        myOLED.print( "Connection to WiFi", LEFT, 16);
        myOLED.print( "FAILED", CENTER, 32);
        myOLED.update();
    }
}
