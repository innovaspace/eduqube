//-----------------------------------------------------------------------------
//  sensors.cpp
//  Mainboard BME680
//  BME280 & MPU9250 initialization and data reading
//-----------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <SPI.h>
#include <MPU9250.h>
#include <INA226.h>
#include "config.h"
#include "functions.h"

extern struct dataStruct myData;    // sctuctured variable declared as external

MPU9250 IMU(Wire,MPU_I2C);          // IMU object to read MPU9250
Adafruit_BME680 bme;                // BME object to read BME680
INA226 ina;                         // INA object to read INA226

boolean bmestatus;
int mpustatus;

//-----------------------------------------------------------------------------
//  Sensors Setup
//  Both sensors are initialized, showing error messages in case of failure
//-----------------------------------------------------------------------------
void sensors_setup()                                    
{
    // BME680
    bmestatus = bme.begin();
    if (!bmestatus) 
    {
        Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    }
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150);
  
    // MPU9250
    mpustatus = IMU.begin();
    if (mpustatus < 0)
    {
        Serial.println("MPU9250 initialization unsuccessful");
    }
    
    //INA226
    ina.begin();
    ina.configure(INA226_AVERAGES_1, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
    ina.calibrate(rshunt, maxcurrent);
}
//-----------------------------------------------------------------------------
//  Read BME
//  BME680 data is read and stored in the structured variable 
//-----------------------------------------------------------------------------
void read_bme()                                         
{
    if (bmestatus)
    {
        bme.performReading();
        myData.t = bme.temperature;                         // Temperaturae
        myData.h = bme.humidity;                            // Humidity
        myData.p = bme.pressure / 100.0;                    // Pressure
        myData.a = bme.readAltitude(SEALEVELPRESSURE_HPA);  // Aprox. altitude
        myData.a /= 2;
        myData.g = bme.gas_resistance / 1000.0;
    }
}
//-----------------------------------------------------------------------------
//  Read MPU
//  MPU9250 data is read and stored in the structured variable
//-----------------------------------------------------------------------------
void read_mpu()                                        
{
    if (mpustatus >= 0) 
    {
        IMU.readSensor();
        myData.ax = IMU.getAccelX_mss();    // X-axis accelerometer
        myData.ay = IMU.getAccelY_mss();    // Y-axis accelerometer
        myData.az = IMU.getAccelZ_mss();    // Z-axis accelerometer
        myData.gx = IMU.getGyroX_rads();    // X-axis gyroscope
        myData.gy = IMU.getGyroY_rads();    // Y-axis gyroscope
        myData.gz = IMU.getGyroZ_rads();    // Z-axis gyroscope
        myData.mgx = IMU.getMagX_uT();      // X-axis magnetometer
        myData.mgy = IMU.getMagY_uT();      // Y-axis magnetometer
        myData.mgz = IMU.getMagZ_uT();      // Z-axis magnetometer
    }
}
//-----------------------------------------------------------------------------
//  Read MPU
//  INA226 data is read and stored in the structured variable 
//-----------------------------------------------------------------------------
void read_ina()
{
    myData.voltage = ina.readBusVoltage();
    myData.power = ina.readBusPower();
    myData.current = ina.readShuntCurrent();
}
