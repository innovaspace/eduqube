#include <Arduino.h>
#include "sensors.h"
#include "gps.h"
#include "config.h"
#include "functions.h"

dataStruct myData;                            //The sctuctured variable is declared as external
byte tx_buf[sizeof(dataStruct)] = {0};        //Array used as buffer for LoRa data transmission, declared in "functions.h"
byte zize;                                    //Variable used to store the data size of the payload data

int initled = LED_BUILTIN_GREEN;
int brightness = 255;                         //How bright the LED is
int fadeAmount = 5;                           //How many points to fade the LED by

//Function to fade the RGB LED, indicating that the OBC program started to run
void startup()
{
  do
  {
    analogWrite(initled, brightness);
    brightness = brightness - fadeAmount;
    if (brightness <= 0) {
      fadeAmount = -fadeAmount;
    }
    delay(30);
  } while (brightness != 255);
  analogWrite(LED_BUILTIN_GREEN, 256);        //Write a value outside the analogWrite function range (0-255) so the LED will turn off completly
}

void reset_wtd (void)                         //Function to tell the watchdog to not reset the microcontroller while working normally
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

//All the functions to obtain the data to be sent are called, and that data is copied from the structured variable to the "tx_buf" array
void get_data()
{
  read_bme();
  read_mpu();
  read_gps();
  read_ina();
  memcpy(tx_buf, &myData, sizeof(myData) );
  zize = sizeof(myData);
}

//A function that print all the stored data in the serial monitor
void print_data()
{
  //BME680
  if (bmestatus)
  {
    Serial.println("BME Readings:");
    Serial.print("Temperatura: ");
    Serial.println(myData.t);
    Serial.print("Humedad: ");
    Serial.println(myData.h);
    Serial.print("Presión: ");
    Serial.println(myData.p);
    Serial.print("Altitud: ");
    Serial.println(myData.a);
    Serial.print("Gas: ");
    Serial.println(myData.g);
  }
  else
  {
    Serial.println("BME not detected");
  }
  //MPU9250
  if (mpustatus >= 0)
  {
    Serial.println("MPU9250 Readings:");
    Serial.print("Acelerometro (X Y Z): ");
    Serial.print(myData.ax);
    Serial.print(" ");
    Serial.print(myData.ay);
    Serial.print(" ");
    Serial.println(myData.az);
    Serial.print("Giroscopo (X Y Z): ");
    Serial.print(myData.gx);
    Serial.print(" ");
    Serial.print(myData.gy);
    Serial.print(" ");
    Serial.println(myData.gz);
    Serial.print("Magnetometro (X Y Z): ");
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
    Serial.println("Posicion");
    Serial.print("Latitud: ");
    Serial.println(myData.g_lat);
    Serial.print("Longitud: ");
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
//Functions used to blink the RGB LED as indicators
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
