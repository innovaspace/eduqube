#include "Arduino.h"
#include <Wire.h>


/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_ADDRESS                         (0x36)    //  (54 decimal)
   
/*=========================================================================*/

/*=========================================================================
    CONFIG REGISTER (R/W)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_Status_Reset                    (0x00)    // Set:0x0020, Reset:0x0000 (POR)
	
    /*---------------------------------------------------------------------*/
    	#define INNOVA_MAX17261_Status_Reset                    	(0x0020)  // Reset Bit
	#define INNOVA_MAX17261_Status_Reset_POR                	(0x0000)  // Reset Bit
	
    	#define INNOVA_MAX17261_REG_CONFIG_DesignCap                	(0x18)    // 0x1388 - Battery design capacity  (DesignCap)
    	#define INNOVA_MAX17261_CONFIG_DesignCap                    	(0x1388)  // 0x1388
	
	#define INNOVA_MAX17261_REG_CONFIG_FullCapRep           	(0x10)    // 0x09C4 - Battery Full capacity capacity  (FullCapRep)
    //	#define INNOVA_MAX17261_CONFIG_FullCapRep                   (0x09C4)  // 0x09C4 - Battery Full capacity capacity  (FullCapRep)
    
	#define INNOVA_MAX17261_REG_CONFIG_dQAcc                    (0x45)    // 0x0027 - Battery design capacity /32  (DesignCap /32 ---> dQAcc
    	#define INNOVA_MAX17261_CONFIG_dQAcc                        (0x0027)  // 0x0027 - Battery design capacity /32  (DesignCap /32 ---> dQAcc
    
	#define INNOVA_MAX17261_REG_CONFIG_dPAcc                    (0x46)    // 0x0190 - dPAcc
    	#define INNOVA_MAX17261_CONFIG_dPAcc                        (0x0190)  // 0x0190 - dPAcc
	
	#define INNOVA_MAX17261_REG_CONFIG_IChgTerm                 (0x1E)    // 0x0080 - Battery charge termination
    	#define INNOVA_MAX17261_CONFIG_IChgTerm                     (0x0080)  // 0x0080 - Battery charge termination
    
	#define INNOVA_MAX17261_REG_CONFIG_VEmpty                   (0x3A)    // 0xA561 - Battery VEmpty
    	#define INNOVA_MAX17261_CONFIG_VEmpty                       (0xA561)  // 0xA561 - Battery VEmpty
    
	#define INNOVA_MAX17261_REG_CONFIG_Miscfg                   (0x2B)    // 0x3870 - Battery Miscfg
	#define INNOVA_MAX17261_CONFIG_Miscfg                       (0x3870)  // 0x3870 - Battery Miscfg
    	#define INNOVA_MAX17261_CONFIG_Miscfg_Quick_Start           (0x1400)  // 0x3870 - Battery Miscfg
    
	#define INNOVA_MAX17261_REG_CONFIG_ModelCfg                 (0xDB)    // 0x0420 - Battery ModelCfg
    	#define INNOVA_MAX17261_CONFIG_ModelCfg                     (0x0420)  // 0x0420 - Battery ModelCfg
    
	#define INNOVA_MAX17261_REG_CONFIG_RComp0                   (0x38)    // 0x004E - Battery RComp0
    	#define INNOVA_MAX17261_CONFIG_RComp0                       (0x004E)  // 0x004E - Battery RComp0

    	#define INNOVA_MAX17261_REG_CONFIG_TempCo                   (0x39)    // 0x263E - Battery TempCo
    	#define INNOVA_MAX17261_CONFIG_TempCo                       (0x263E)  // 0x263E - Battery TempCo
	
    	#define INNOVA_MAX17261_REG_Command_HipCfg                  (0x60)    // 0x0090 - 0x0000 - exit Hibernate mode step 1 & 3 - COMMAND HipCfg
    	#define INNOVA_MAX17261_Command_HipCfg_Exit1                (0x0090)  // 0x0090 - 0x0000 - exit Hibernate mode step 1 & 3 - COMMAND HipCfg
    	#define INNOVA_MAX17261_Command_HipCfg_Exit3                (0x0000)  // 0x0090 - 0x0000 - exit Hibernate mode step 1 & 3 - COMMAND HipCfg
    
	#define INNOVA_MAX17261_REG_CONFIG_HipCfg                   (0xBA)    // 0x0000 - exit Hibernate mode step 2 (Active mode)
    	#define INNOVA_MAX17261_CONFIG_HipCfg                       (0x0000)  // 0x0000 - exit Hibernate mode step 2 (Active mode)
 
    #define INNOVA_MAX17261_REG_TempNTC                         (0x1D)    // 0x1D Config - TSEL 
        #define INNOVA_MAX17261_CONFIG_TempNTC                  (0xA210)  // 0xA210 Config parameter TSEL = 1
    
	
	
/*=========================================================================*/


/*=========================================================================
    Battery VOLTAGE REGISTER (R)  (VCell)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_VCELL                          (0x09)
/*=========================================================================*/

/*=========================================================================
    CURRENT REGISTER (R)  (Current)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_CURRENT                        (0x0A)
/*=========================================================================*/

/*=========================================================================
    CURRENT REGISTER (R)  (AvgCurrent)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_AVGCURRENT                     (0x0B)
/*=========================================================================*/

/*=========================================================================
    SOC REGISTER (R)  (RepSOC)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_RepSOC                         (0x06)
/*=========================================================================*/

/*=========================================================================
    Reported Capacity REGISTER (R)   (RepCap)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_RepCap                         (0x05)
/*=========================================================================*/

/*=========================================================================
    Full Capacity REGISTER (R)       (FullRepCap)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_FullRepCap                     (0x10)
/*=========================================================================*/

/*=========================================================================
    Die Tempetarure REGISTER (R)    (Temp)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_Temp                           (0x08)
/*=========================================================================*/

/*=========================================================================
    Time to Empty REGISTER (R)   (TTE)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_TTE                           (0x11)
/*=========================================================================*/

/*=========================================================================
    Time to Full REGISTER (R)   (TTF)
    -----------------------------------------------------------------------*/
    #define INNOVA_MAX17261_REG_TTF                           (0x20)
/*=========================================================================*/

class INNOVA_MAX17261{
 public:
  INNOVA_MAX17261(uint8_t addr = INNOVA_MAX17261_ADDRESS);
  void begin(void);
  void setConfigRegister(void);
  void setCalibrate(byte);
  float getVoltageCell(void);
  float getRepSOC(void);
  float getCurrent_mA(int16_t);
  float getAvgCurrent_mA(int16_t);
  float getFullRepCap(void);
  float getRepCap(void);
  float getTemp(void);
  float getTTE(void);
  float getTTF(void);

  void reset();
  void quickStart();

 private:
  uint8_t INNOVA_MAX17261_i2caddr;   
  byte INNOVA_MAX17261_CONFIG_FullCapRep;
  void writeRegister(uint8_t reg, uint16_t value);
  void readRegister(uint8_t reg, uint16_t *value);
  void readbyteRegister(byte reg, byte &MSB, byte &LSB);
  int16_t getRepSOC_raw(void);
  int16_t getCurrent_raw(void);
  int16_t getAvgCurrent_raw(void);
  int16_t getFullRepCap_raw(void);
  int16_t getRepCap_raw(void);
  int16_t getTemp_raw(void);
  int16_t getTTE_raw(void);
  int16_t getTTF_raw(void);
};