# EDUQUBE EXAMPLE CODES

#### Mainboard 
Main OBC code, reads all the sensors data and sends it to the Ground Station via LoRa.

#### Ground Station
Recieves all the payload data, shows it in Serial Monitor and uploads it to an MQTT server. <br>
<br>
To upload the data to the MQTT server: 
- Uncomment the commented lines in main.ino
- Set WiFi SSID and password in config.h
- Set MQTT server IP in config.h

## Library Dependencies
To run each code, you need to have the following libraries installed:

#### Mainboard
- RadioHead (RH_RF95)
- TinyGPS++
- Adafruit Sensor
- Adafruit BME280 (or Adafruit BME680)
- MPU9250
- INA226

#### Ground Station
- RadioHead (RH_RF95)
- OLED_I2C
- PubSubClient
- WiFi
