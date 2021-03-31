#include "mqtt.h"
#include "wifi_c.h"
#include "config.h"
#include "display.h"

//
PubSubClient client(wifiClient);

void mqttConnect()
{
  //The MQTT server IP and port are set
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  // Loop until MQTT client is reconnected
  while (!client.connected())
  {
    //The status is printed in the serial monitor and in the OLED screen
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
  client.publish(launchdate_topic, launch_date, true); //Launch date is published, adding the value "true" for the message to be retained in the MQTT server

  //After establishing connection with the MQTT broker, a message showing the status is printed in the OLED
  print_status();
}

//A loop that checks if the client is connected and calls the function reconnect in case that it isn't.
void mqtt_loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
