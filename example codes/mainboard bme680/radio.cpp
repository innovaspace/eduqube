/*
RFM95 LoRa radio control
The module is initialized with the frequency, transmit power and spreading factor parameters stablished in the config file
The function that transmits the data via LoRa and recieves an ack from the ground station is defined
*/

#include <RH_RF95.h>
#include "config.h"
#include "functions.h"
#include "radio.h"

RH_RF95 rf95(RFM95_CS,RFM95_INT);                                         //An object of the class RH_RF95 is initialized

void radio_setup() 
{
  if (!rf95.init())                                                       //RFM95 is initialized, a message is printed in case of failure
    Serial.println("RFM95 init failed");
  rf95.setTxPower(TX_POWER, false);                                       //Transmitt power is set
  rf95.setSpreadingFactor(SF);                                            //Spreading Factor is set
  rf95.setFrequency(FREQ);                                                //Transmision frequency is set
  if(!rf95.setFrequency(FREQ))                                            //A message is printed if the frequency can't be set
  {
    Serial.print("Transmition frequency could not be set correctly");
  }
}
void send_data()
{
  Serial.println("Sending data to Ground Station");
  blink_blue_2();                                                         //Blue LED is blinked two times to indicate that the message was transmitted
  rf95.send((uint8_t *)tx_buf, zize);                                     //All the data stored in the "tx_buf" array is sent
  rf95.waitPacketSent();                                                  //Wait for the packet to be sent
  //Wait for a reply
  uint8_t indatabuf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(indatabuf);
  if (rf95.waitAvailableTimeout(3000))
  { 
    if (rf95.recv(indatabuf, &len))                                       //If a reply is obtained
   {
      blink_green();                                                      //Green LED is blinked to indicate that an ack was recieved
      Serial.print("Got a reply: ");                                      //The recieved message and the RSSI are printed in Serial monitor
      Serial.println((char*)indatabuf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC); 
   }
     else
     {
      //If a reply was obtained but the message couldn't be decodified, a message indicating the failure on reception is printed
      Serial.println("Reception failed");
     }
  }
  else
  {
    blink_red();                                                          //Red LED is blinked if there was no reply
    Serial.println("No reply");                                           //A message is printed indicating that there was no reply
  }
}
