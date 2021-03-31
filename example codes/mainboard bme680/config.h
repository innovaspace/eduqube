/*
  General configuration file
*/

#ifndef CONFIG_H
#define CONFIG_H

// -----------------------------------------------------------------------------------------------------
// LoRa
// -----------------------------------------------------------------------------------------------------
#define TX_POWER 20                         //Transmission power in dBm (Possible values = 2-20)
#define SF 12                               //Spreading Factor (Possible values = 6-12)
#define RFM95_CS 16                         //Pin connected to radio Chip Select
#define RFM95_INT 9                         //Pin connected to radio interrupt pin
#define FREQ 915.0                          //RFM95 transmission frequency

// -----------------------------------------------------------------------------------------------------
// BME680 & MPU9250
// -----------------------------------------------------------------------------------------------------
#define SEALEVELPRESSURE_HPA (1026)         //Sea level pressure, used to calibrate BME680 sensor
#define MPU_I2C 0x68                        //MPU9250 I2C adress

// -----------------------------------------------------------------------------------------------------
// Watchdog
// -----------------------------------------------------------------------------------------------------
#define wdi_reset 2                         //Pin connected to watchdog reset pin

// -----------------------------------------------------------------------------------------------------
// GPS
// -----------------------------------------------------------------------------------------------------
static const uint32_t GPSBaud = 9600;       //GPS module baudrate

// -----------------------------------------------------------------------------------------------------
// FLASH Memory
// -----------------------------------------------------------------------------------------------------
#define AT25_CS 8                           //Pin connected to flash memory Chip Select

// -----------------------------------------------------------------------------------------------------
// INA226 Current / Power Monitor
// -----------------------------------------------------------------------------------------------------
#define rshunt 0.06                         //Shunt resistor value, used to calibrate INA226 sensor 
#define maxcurrent 1                        //Max expected current

#endif
