# EDUQUBE EXAMPLE CODES

## Mainboard 
Main OBC code, reads all the sensors data and sends it to the Ground Station via LoRa

## Ground Station
Recieves all the payload data, shows it in Serial Monitor and uploads it to an MQTT server <br>
To upload the data to the MQTT server: 
- Uncomment the commented lines in main.ino
- Set WiFi SSID and password in config.h
- Set MQTT server IP in config.h
