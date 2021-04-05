//-----------------------------------------------------------------------------
//  main.ino
//  Ground Station
//  
//  Main program
//  sequence of configuration functions is ordered in setup()
//  sequence of functions to be excecuted in loop in loop()
//-----------------------------------------------------------------------------

#include <Arduino.h>
#include "radio.h"
#include "config.h"
#include "mqtt.h"
#include "wifi_c.h"
#include "upload.h"
#include "display.h"

//-----------------------------------------------------------------------------
//  Setup
//-----------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);
    oled_setup();
    radio_setup();
    //wifi_setup();
    //mqttConnect();
    //upload_data();
    print_status();
}
//-----------------------------------------------------------------------------
//  Loop
//-----------------------------------------------------------------------------
void loop()
{
    radio_loop();
    //upload_data();
    //mqtt_loop();
}
