#include "radio.h"
#include "config.h"
#include "functions.h"
#include "display.h"

RH_RF95 rf95(RFM95_CS, RFM95_INT);                                        //An object of the class RH_RF95 is initialized
extern struct dataStruct myData;                                          //The sctuctured variable is declared as external
char cstr[16];
char cstr2[16];
unsigned int packet;
void radio_setup()
{
  if (!rf95.init())                                                       //RFM95 is initialized, a message is printed in case of failure
    Serial.println("RF95 init failed");
  rf95.setTxPower(TX_POWER, false);                                       //Transmitt power is set
  rf95.setSpreadingFactor(SF);                                            //Spreading Factor is set
  rf95.setFrequency(FREQ);                                                //Transmision frequency is set
  if (!rf95.setFrequency(FREQ))                                           //A message is printed if the frequency can't be set
  {
    Serial.print("Transmition frequency could not be set correctly");
  }
}

void radio_loop()
{
  if (rf95.available())
    //Wait for a message
  {
    Serial.println("Waiting for messages...");
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      // A message indicating that a LoRa packet was recieved is printed in the serial monitor
      Serial.println("Message recieved from EduQube");
      memcpy(&myData, buf, sizeof(myData));
      //The "packet" variable is increased to count the number of packets recieved
      packet++;

      // An ACK is sent as a reply
      uint8_t data[] = "Data recieved succesfully";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();

      //Status is shown in the OLED screen
      myOLED.clrScr();
      myOLED.print("EduQube GND Station", CENTER, 0);
      myOLED.print("Recieved packets:", LEFT, 16);
      sprintf(cstr, "%d", packet);
      myOLED.print(cstr, 105, 16);
      sprintf(cstr2, "RSSI: %d dB", rf95.lastRssi());
      myOLED.print(cstr2, LEFT, 32);
      myOLED.update();

      //All the recieved data is shown in the serial monitor
      print_data();

    }
    else
    {
      //If a message is recieved but it can't be decodified, a message is shown indicating the failure in reception
      Serial.println("reception failed");
    }
    //The recieved signal strength is stored in the data structure
    myData.rssi = rf95.lastRssi();
  }
}
