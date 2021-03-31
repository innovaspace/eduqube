#include <Arduino.h>
#include "display.h"
OLED  myOLED(4, 15, 16);    // Start an instance of the OLED class with I2C (OLED_SDA, OLED_SCL, OLED_RST)
extern uint8_t SmallFont[]; // Declaring a font array to be used in the OLED screen
extern uint8_t logo[];      // Declaring a logo array to be shown in the startup

void oled_setup()
{
  //Initialize a 128x64 display, if a 0 is returned by the function, an error mesagge is printed in Serial
  if (!myOLED.begin(SSD1306_128X64))
  {
    Serial.println("Failed memory allocation...");  // In case the library failed to allocate enough RAM for the display buffer...
  }
  myOLED.setFont(SmallFont);                        // Select the font called SmallFont
  myOLED.clrScr();                                  // Clear the screen buffer
  myOLED.drawBitmap(32, 0, logo, 64, 64);           // Draw a 64x64 pixel bitmap (EduQube logo)
  myOLED.update();                                  // Copy the screen buffer
  delay(2000);                                      // Stop the code for 2 seconds to keep the logo visible
}

//Prints a message in the OLED screen to show the status
void print_status()
{
  myOLED.clrScr();
  myOLED.print( "EduQube GND Station", CENTER, 0);
  myOLED.print( "Waiting to receive ", LEFT, 16);
  myOLED.print( "LoRa packets", LEFT, 32);
  myOLED.update();
}
