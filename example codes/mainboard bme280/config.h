//-----------------------------------------------------------------------------
//  config.h
//  Mainboard BME280
//  General configuration file
//-----------------------------------------------------------------------------

#ifndef CONFIG_H
#define CONFIG_H

//-----------------------------------------------------------------------------
//  LoRa
//-----------------------------------------------------------------------------
#define TX_POWER 20         // Transmission power in dBm (range = 2-20)
#define SF 12               // Spreading Factor (range = 6-12)
#define RFM95_CS  16        // Pin connected to radio Chip Select
#define RFM95_INT 9         // Pin connected to radio interrupt pin
#define FREQ 915.0          // RFM95 transmission frequency

//-----------------------------------------------------------------------------
//  BME280 & MPU9250
//-----------------------------------------------------------------------------
#define SEALEVELPRESSURE_HPA (1026)     // BME680 Sea level pressure (calibration)
#define MPU_I2C 0x68                    // MPU9250 I2C address

//-----------------------------------------------------------------------------
//  Watchdog
//-----------------------------------------------------------------------------
#define wdi_reset 2                     // Watchdog reset pin

//-----------------------------------------------------------------------------
//  GPS
//-----------------------------------------------------------------------------
static const uint32_t GPSBaud = 9600;   // GPS module baudrate

//-----------------------------------------------------------------------------
//  FLASH Memory
//-----------------------------------------------------------------------------
#define AT25_CS 8                       // flash memory Chip Select

//-----------------------------------------------------------------------------
//  INA226 Current / Power Monitor
//-----------------------------------------------------------------------------
#define rshunt 0.06                     // INA226 Shunt resistor value
#define maxcurrent 1                    // Max expected current (in Amperes)

#endif
