//-----------------------------------------------------------------------------
//  mqtt.cpp
//  Ground Station
//-----------------------------------------------------------------------------

#include "mqtt.h"
#include "wifi_c.h"
#include "config.h"
#include "display.h"

PubSubClient client(wifiClient);

//-----------------------------------------------------------------------------
//  MQTT Connect
//  Set MQTT server IP and port
//-----------------------------------------------------------------------------
void mqttConnect()
{
    client.setServer(mqtt_server, 1883);
}
//-----------------------------------------------------------------------------
//  Reconnect
//-----------------------------------------------------------------------------
void reconnect() 
{
    // Loop until MQTT client is reconnected
    while (!client.connected())
    {
        // Print status in serial monitor and OLED screen
        Serial.print("Attempting MQTT connection...");
        myOLED.clrScr();
        myOLED.print( "EduQube GND Station", CENTER, 0);
        myOLED.print( "Connecting to MQTT", LEFT, 16);
        myOLED.print( "server", LEFT, 32);
        myOLED.update();

        // Attempt to connect
        if (client.connect("gndstation"))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
    
    // Launch date is published. Add "true" for the message to be retained in the MQTT server
    client.publish(launchdate_topic, launch_date, true); 

    // After establishing connection with the MQTT broker, print a message showing the status in OLED
    print_status();
}
//-----------------------------------------------------------------------------
//  MQTT Loop
//  Checks if the client is connected and calls the function reconnect if not
//-----------------------------------------------------------------------------
void mqtt_loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    
    client.loop();
}
