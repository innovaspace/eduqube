//-----------------------------------------------------------------------------
//  functions.cpp
//  Mainboard BME680
//-----------------------------------------------------------------------------

#include <Arduino.h>
#include "sensors.h"
#include "gps.h"
#include "config.h"
#include "functions.h"

// sctuctured variable is declared as external
dataStruct myData;                            

// buffer for LoRa data transmission, declared in "functions.h"
byte tx_buf[sizeof(dataStruct)] = {0};        

// data size of the payload data
byte zize;                                    

int initled = LED_BUILTIN_GREEN;
int brightness = 255;                         //LED brightness
int fadeAmount = 5;                           //LED fading points

//-----------------------------------------------------------------------------
//  Startup
//  fading RGB LED. Indicates OBC program running
//-----------------------------------------------------------------------------
void startup()
{
    do
    {
        analogWrite(initled, brightness);
        brightness = brightness - fadeAmount;
        if (brightness <= 0) 
        {
            fadeAmount = -fadeAmount;
        }
        delay(30);
    } while (brightness != 255);
    
    // Write a value outside the analogWrite function range (0-255)
    // LED will turn off completly
    analogWrite(LED_BUILTIN_GREEN, 256);        
}
//-----------------------------------------------------------------------------
//  Reset Watchdog
//  Force watchdog to not reset the microcontroller while working normally
//-----------------------------------------------------------------------------
void reset_wtd (void)                         
{
    if (digitalRead(wdi_reset) == 0)
    {
        digitalWrite(wdi_reset, HIGH);
    }
    else
    {
        digitalWrite(wdi_reset, LOW);
    }
}
//-----------------------------------------------------------------------------
//  Get Data
//  call functions to obtain the data to be sent
//  data is copied from the structured variable to the "tx_buf" array
//-----------------------------------------------------------------------------
void get_data()
{
    read_bme();
    read_mpu();
    read_gps();
    read_ina();
    memcpy(tx_buf, &myData, sizeof(myData) );
    zize = sizeof(myData);
}
//-----------------------------------------------------------------------------
//  Print Data
//  print all the stored data in the serial monitor
//-----------------------------------------------------------------------------
void print_data()
{
    // BME680
    if (bmestatus)
    {
        Serial.println("BME Readings:");
        Serial.print("Temperature: ");
        Serial.println(myData.t);
        Serial.print("Humidity: ");
        Serial.println(myData.h);
        Serial.print("Pressure: ");
        Serial.println(myData.p);
        Serial.print("Altitude: ");
        Serial.println(myData.a);
        Serial.print("Gas: ");
        Serial.println(myData.g);
    }
    else
    {
        Serial.println("BME not detected");
    }

    // MPU9250
    if (mpustatus >= 0)
    {
        Serial.println("MPU9250 Readings:");
        Serial.print("Acelerometer (X Y Z): ");
        Serial.print(myData.ax);
        Serial.print(" ");
        Serial.print(myData.ay);
        Serial.print(" ");
        Serial.println(myData.az);
        Serial.print("Gyroscope (X Y Z): ");
        Serial.print(myData.gx);
        Serial.print(" ");
        Serial.print(myData.gy);
        Serial.print(" ");
        Serial.println(myData.gz);
        Serial.print("Magnetometer (X Y Z): ");
        Serial.print(myData.mgx);
        Serial.print(" ");
        Serial.print(myData.mgy);
        Serial.print(" ");
        Serial.println(myData.mgz);
    }
    else
    {
        Serial.println("MPU9250 not detected");
    }

    //GPS
    if (gpsstatus)
    {
        Serial.println("Position");
        Serial.print("Latitude: ");
        Serial.println(myData.g_lat);
        Serial.print("Longitude: ");
        Serial.println(myData.g_lng);
    }
    else
    {
        Serial.println("GPS not detected");
    }

    if (myData.voltage <= 0.1)
    {
        Serial.println("INA226: Battery not connected, can't measure power while being powered by usb");
    }
    else
    {
        Serial.println("INA226 Readings:");
        Serial.print("Battery voltage: ");
        Serial.print(myData.voltage, 3);
        Serial.println(" V");
        Serial.print("System bus power: ");
        Serial.print(myData.power, 3);
        Serial.println(" W");
        Serial.print("System current: ");
        Serial.print(myData.current, 3);
        Serial.println(" A");
    }
}
//-----------------------------------------------------------------------------
//  Blinking LED
//  Functions used to blink the RGB LED as indicators
//-----------------------------------------------------------------------------
void blink_red()
{
    digitalWrite(LED_BUILTIN_RED, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN_RED, HIGH);
}

void blink_green()
{
    analogWrite(LED_BUILTIN_GREEN, 0);
    delay(100);
    analogWrite(LED_BUILTIN_GREEN, 256);
}

void blink_blue_2()
{
    digitalWrite(LED_BUILTIN_BLUE, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN_BLUE, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN_BLUE, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN_BLUE, HIGH);
}
