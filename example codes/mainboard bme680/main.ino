//-----------------------------------------------------------------------------
//  main.ino
//  Mainboard BME680
//  
//  Main program
//  sequence of configuration functions is ordered in setup()
//  sequence of functions to be excecuted in loop in loop()
//-----------------------------------------------------------------------------

#include <Arduino.h>
#include "gps.h"
#include "config.h"
#include "radio.h"
#include "functions.h"
#include "sensors.h"

//-----------------------------------------------------------------------------
//  Setup
//-----------------------------------------------------------------------------
void setup()
{
    pinMode(LED_BUILTIN_RED, OUTPUT);       // RGB LED pins as outputs
    pinMode(LED_BUILTIN_GREEN, OUTPUT);
    pinMode(LED_BUILTIN_BLUE, OUTPUT);
    pinMode(wdi_reset, OUTPUT);             // watchdog reset pin as output
    pinMode(RADIO_RESET_PIN, INPUT);        // RFM95 reset pin as input for high impedance
    pinMode(AT25_CS, OUTPUT);
    digitalWrite(AT25_CS, HIGH);            // Flash mem Chip Select set to HIGH to not interfere with RFM95
    digitalWrite(LED_BUILTIN_RED, HIGH);
    digitalWrite(LED_BUILTIN_GREEN, HIGH);
    digitalWrite(LED_BUILTIN_BLUE, HIGH);
    startup();
    Serial.begin(9600);
    radio_setup();
    gps_setup();
    sensors_setup();
}
//-----------------------------------------------------------------------------
//  Loop
//-----------------------------------------------------------------------------
void loop()
{
    reset_wtd();
    get_data();
    send_data();
    print_data();
    delay(400);
}
