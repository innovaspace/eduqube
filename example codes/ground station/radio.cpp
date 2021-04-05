//-----------------------------------------------------------------------------
//  radio.cpp
//  Ground Station
//-----------------------------------------------------------------------------

#include "radio.h"
#include "config.h"
#include "functions.h"
#include "display.h"

RH_RF95 rf95(RFM95_CS, RFM95_INT);          // Init object of the class RH_RF95

extern struct dataStruct myData;            // The sctuctured variable is declared as external

char cstr[16];
char cstr2[16];
unsigned int packet;

//-----------------------------------------------------------------------------
//  Radio Setup
//-----------------------------------------------------------------------------
void radio_setup()
{
    if (!rf95.init())                         // Init RFM95, print a message if fail
        Serial.println("RF95 init failed");     
    rf95.setTxPower(TX_POWER, false);         // set Transmitt power
    rf95.setSpreadingFactor(SF);              // set Spreading Factor
    rf95.setFrequency(FREQ);                  // set Transmision frequency
    if (!rf95.setFrequency(FREQ))             // print message if frequency can't be set
    {
        Serial.print("Transmition frequency could not be set correctly");
    }
}
//-----------------------------------------------------------------------------
//  Radio Loop
//-----------------------------------------------------------------------------
void radio_loop()
{
    if (rf95.available())
    // Wait for a message
    {
        Serial.println("Waiting for messages...");
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        
        if (rf95.recv(buf, &len))
        {
            // Print message in serial monitor indicating that a LoRa packet was recieved
            Serial.println("Message recieved from EduQube");
            memcpy(&myData, buf, sizeof(myData));

            // Increase "packet" variable to count the number of packets recieved
            packet++;

            // sent ACK as a reply
            uint8_t data[] = "Data recieved succesfully";
            rf95.send(data, sizeof(data));
            rf95.waitPacketSent();

            // show Status in OLED screen
            myOLED.clrScr();
            myOLED.print("EduQube GND Station", CENTER, 0);
            myOLED.print("Recieved packets:", LEFT, 16);
            sprintf(cstr, "%d", packet);
            myOLED.print(cstr, 105, 16);
            sprintf(cstr2, "RSSI: %d dB", rf95.lastRssi());
            myOLED.print(cstr2, LEFT, 32);
            myOLED.update();

            // show All recieved data in serial monitor
            print_data();
        }
        else
        {
            // If a message is recieved but it can't be decodified, show message indicating failure in reception
            Serial.println("reception failed");
        }

        // store recieved signal strength in data structure
        myData.rssi = rf95.lastRssi();
    }
}