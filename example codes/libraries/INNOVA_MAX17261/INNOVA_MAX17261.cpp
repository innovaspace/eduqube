#include "Arduino.h"
#include <Wire.h>
#include "INNOVA_MAX17261.h"

/**************************************************************************/
/*! 
    @brief  Instantiates a new INNOVA_MAX17261 class
*/
/**************************************************************************/
INNOVA_MAX17261::INNOVA_MAX17261(uint8_t addr) {
  INNOVA_MAX17261_i2caddr = addr;
}

void INNOVA_MAX17261::readRegister(byte reg, uint16_t *value) 
{
	byte MSB = 0;
	byte LSB = 0;
    Wire.beginTransmission(INNOVA_MAX17261_i2caddr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(INNOVA_MAX17261_i2caddr, 2);
	LSB = Wire.read();
	MSB = Wire.read();
    *value = (MSB << 8) | LSB;	
}

void INNOVA_MAX17261::readbyteRegister(byte reg, byte &MSB, byte &LSB) {
	Wire.beginTransmission(INNOVA_MAX17261_i2caddr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(INNOVA_MAX17261_i2caddr, 2);
	LSB = Wire.read();
	MSB = Wire.read();
}

void INNOVA_MAX17261::writeRegister(byte reg, uint16_t value) 
{
	byte MSB = 0;
	byte LSB = 0;
   	MSB = (value >> 8) & 0xFF;
	LSB = value & 0xFF;
	Wire.beginTransmission(INNOVA_MAX17261_i2caddr);
	Wire.write(reg);
	Wire.write(LSB);
	Wire.write(MSB);
	Wire.endTransmission();
}


/**************************************************************************/
/*! 
    @brief  Configures to INNOVA_MAX17261
			
*/
/**************************************************************************/

void INNOVA_MAX17261::setCalibrate(byte _reg){
	INNOVA_MAX17261_CONFIG_FullCapRep = _reg;
}

void INNOVA_MAX17261::setConfigRegister(void)
{
  // Sets battery capacity to 2500mA and correct battery model
  // Set Battery Config registers 
	writeRegister(INNOVA_MAX17261_REG_Status_Reset, INNOVA_MAX17261_Status_Reset);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_DesignCap, INNOVA_MAX17261_CONFIG_DesignCap);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_FullCapRep, INNOVA_MAX17261_CONFIG_FullCapRep);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_dQAcc, INNOVA_MAX17261_CONFIG_dQAcc);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_dPAcc, INNOVA_MAX17261_CONFIG_dPAcc);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_IChgTerm, INNOVA_MAX17261_CONFIG_IChgTerm);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_VEmpty, INNOVA_MAX17261_CONFIG_VEmpty);
	writeRegister(INNOVA_MAX17261_REG_Command_HipCfg, INNOVA_MAX17261_Command_HipCfg_Exit1);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_HipCfg, INNOVA_MAX17261_CONFIG_HipCfg);
	writeRegister(INNOVA_MAX17261_REG_Command_HipCfg, INNOVA_MAX17261_Command_HipCfg_Exit3);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_Miscfg, INNOVA_MAX17261_CONFIG_Miscfg);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_ModelCfg, INNOVA_MAX17261_CONFIG_ModelCfg);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_RComp0, INNOVA_MAX17261_CONFIG_RComp0);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_TempCo, INNOVA_MAX17261_CONFIG_TempCo);
	writeRegister(INNOVA_MAX17261_REG_Status_Reset, INNOVA_MAX17261_Status_Reset_POR);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_HipCfg, INNOVA_MAX17261_CONFIG_HipCfg);
	writeRegister(INNOVA_MAX17261_REG_TempNTC, INNOVA_MAX17261_CONFIG_TempNTC);
}

/**************************************************************************/
/*! 
    @brief  Setups the HW 
*/
/**************************************************************************/
void INNOVA_MAX17261::begin(void) {
  Wire.begin();    
  // Set chip to large range config values to start
  setConfigRegister();
}

/**************************************************************************/
/*! 
    @brief  Gets the raw State Of Charge SOC (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getRepSOC_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_RepSOC, &value);
  return (int16_t)value;
}

/**************************************************************************/
/*! 
    @brief  Gets the raw current value (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getCurrent_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_CURRENT, &value);
  return (int16_t)value;
}

/**************************************************************************/
/*! 
    @brief  Gets the raw Average current value (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getAvgCurrent_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_AVGCURRENT, &value);
  return (int16_t)value;
}
 
/**************************************************************************/
/*! 
    @brief  Gets the raw Reported Capacity value (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getRepCap_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_RepCap, &value);
  return (int16_t)value;
}

/**************************************************************************/
/*! 
    @brief  Gets the raw Full Reported Capacity value (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getFullRepCap_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_FullRepCap, &value);
  return (int16_t)value;
}

/**************************************************************************/
/*! 
    @brief  Gets the raw Temperature value (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getTemp_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_Temp, &value);
  return (int16_t)value;
}

/**************************************************************************/
/*! 
    @brief  Gets the raw Time to Empty value (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getTTE_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_TTE, &value);
  return (int16_t)value;
}

/**************************************************************************/
/*! 
    @brief  Gets the raw Time to Full value (16-bit signed integer, so +-32767)
*/
/**************************************************************************/
int16_t INNOVA_MAX17261::getTTF_raw() {
  uint16_t value;
  readRegister(INNOVA_MAX17261_REG_TTF, &value);
  return (int16_t)value;
}

/**************************************************************************/
/*! 
    @brief  Gets the current value in mA
*/
/**************************************************************************/
float INNOVA_MAX17261::getCurrent_mA(int16_t _n) {
  int16_t valueDec = getCurrent_raw();
  return valueDec * _n / 1000;
}

/**************************************************************************/
/*! 
    @brief  Gets the Average current value in mA
*/
/**************************************************************************/
float INNOVA_MAX17261::getAvgCurrent_mA(int16_t _n) {
  int16_t valueDec = getAvgCurrent_raw();
  return valueDec * _n / 1000 ;
}

/**************************************************************************/
/*! 
    @brief  Gets the Battery Voltage value in volts
*/
/**************************************************************************/

float INNOVA_MAX17261::getVoltageCell() {
  int value;
  byte MSB = 0;
  byte LSB = 0;
  readbyteRegister(INNOVA_MAX17261_REG_VCELL, MSB, LSB);
  value =  ((MSB << 8) | LSB);
  value = ((value / 16) * 1.25);
  return value;
}

/**************************************************************************/
/*! 
    @brief  Gets the Battery SOC (State of Charge) value in Percent
*/
/**************************************************************************/
float INNOVA_MAX17261::getRepSOC() {	
	int16_t valueDec = getRepSOC_raw();
  	return valueDec / 256 ;	
}

/**************************************************************************/
/*! 
    @brief  Gets the Battery Full Capacity value in mAh
*/
/**************************************************************************/

float INNOVA_MAX17261::getFullRepCap() {
	int16_t valueDec = getFullRepCap_raw();
  	return valueDec;	
}


/**************************************************************************/
/*! 
    @brief  Gets the Battery Reported Capacity value in mAh
*/
/**************************************************************************/
float INNOVA_MAX17261::getRepCap() {
	int16_t valueDec = getRepCap_raw();
  	return valueDec;	
}

/**************************************************************************/
/*! 
    @brief  Gets the Temperature value in Celcius
*/
/**************************************************************************/
float INNOVA_MAX17261::getTemp() {
	
	int16_t valueDec = getTemp_raw();
  	return valueDec / 256.0 ;	
}

/*! 
    @brief  Gets the Time to Empty value in hours
*/
/**************************************************************************/
float INNOVA_MAX17261::getTTE() {	
	int16_t valueDec = getTTE_raw();
  	return valueDec / 640.002 ;	
}

/*! 
    @brief  Gets the Time to Full value in hours
*/
/**************************************************************************/
float INNOVA_MAX17261::getTTF() {	
	int16_t valueDec = getTTF_raw();
  	return valueDec / 640.002 ;	
}

void INNOVA_MAX17261::reset() {
	writeRegister(INNOVA_MAX17261_REG_Status_Reset, INNOVA_MAX17261_Status_Reset);
}	

void INNOVA_MAX17261::quickStart() {	
	writeRegister(INNOVA_MAX17261_REG_Status_Reset, INNOVA_MAX17261_Status_Reset);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_Miscfg, INNOVA_MAX17261_CONFIG_Miscfg);
	writeRegister(INNOVA_MAX17261_REG_Status_Reset, INNOVA_MAX17261_Status_Reset_POR);
	writeRegister(INNOVA_MAX17261_REG_CONFIG_HipCfg, INNOVA_MAX17261_CONFIG_HipCfg);
}
