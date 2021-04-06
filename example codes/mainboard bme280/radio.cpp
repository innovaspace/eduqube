//-----------------------------------------------------------------------------
//  radio.cpp
//  Mainboard BME280
//  RFM95 LoRa radio control
//  Init module with freq, transmit power and spreading factor of config file
//  Function for tx data via LoRa and rx ACK from ground station
//-----------------------------------------------------------------------------

#include <RH_RF95.h>
#include "config.h"
#include "functions.h"
#include "radio.h"

RH_RF95 rf95(RFM95_CS,RFM95_INT);   // Init object of the class RH_RF95

//-----------------------------------------------------------------------------
//  Radio Setup
//  Init RFM95. Print message in case of failure
//-----------------------------------------------------------------------------
void radio_setup() 
{
  if (!rf95.init())                    
    Serial.println("RFM95 init failed");
  rf95.setTxPower(TX_POWER, false);     // set Tx power
  rf95.setSpreadingFactor(SF);          // set Spreading Factor
  rf95.setFrequency(FREQ);              // set Tx frequency
  if(!rf95.setFrequency(FREQ))
  {
    // Print message if freq can't be set
    Serial.print("Transmition frequency could not be set correctly");
  }
}

//-----------------------------------------------------------------------------
//  Send Data
//-----------------------------------------------------------------------------
void send_data()
{
  Serial.println("Sending data to Ground Station");

  // Blue LED blink two times if message was transmitted
  blink_blue_2();

  // Sent data stored in "tx_buf"
  rf95.send((uint8_t *)tx_buf, zize);

  // Wait for the packet to be sent
  rf95.waitPacketSent();
  
  // Wait for a reply
  uint8_t indatabuf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(indatabuf);

  if (rf95.waitAvailableTimeout(3000))
  { 
    if (rf95.recv(indatabuf, &len))
   {
      // Reply is obtained

      // Green LED blink indicate ACK was recieved
      blink_green();

      // Print recieved message and RSSI
      Serial.print("Got a reply: ");
      Serial.println((char*)indatabuf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC); 
   }
     else
     {
      // reply was obtained but message couldn't be decodified
      // print message indicating failure on reception
      Serial.println("Reception failed");
     }
  }
  else
  {
    // Red LED blinks if there was no reply
    blink_red();
    
    // Print message indicating there was no reply
    Serial.println("No reply");
  }
}
