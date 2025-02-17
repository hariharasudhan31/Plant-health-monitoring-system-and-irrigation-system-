# Soil Moisture Monitoring and Irrigation System with Weather Integration

This project is designed to automatically monitor soil moisture levels and control a water pump based on moisture readings and weather conditions. It integrates with the ThingSpeak API to check weather data for rain, and if no rain is detected, the pump is activated. The system uses an ESP8266 microcontroller, a soil moisture sensor, and a relay to control the water pump.

## Features:
- Monitors soil moisture using a soil moisture sensor.
- Checks weather conditions using the ThingSpeak API.
- Turns on the water pump when the soil moisture is low and it is not raining.
- Turns off the water pump when soil moisture is sufficient or it is raining.

## Components Used:
- **ESP8266 WiFi Module**
- **Soil Moisture Sensor** (analog output)
- **Relay** (to control the water pump)
- **Water Pump**
- **Wi-Fi Network** (for internet connectivity)
- **ThingSpeak API** (for weather data)

## Libraries:
- `ESP8266WiFi.h` - Wi-Fi connectivity
- `Wire.h` - I2C communication (if needed)
- `WiFiClient.h` - HTTP communication
- `ESP8266WebServer.h` - Web server for handling requests

## Installation:
1. **Install Libraries:**
   - Open Arduino IDE.
   - Go to **Sketch** → **Include Library** → **Manage Libraries**.
   - Search and install the `ESP8266` package.
   - Install the `WiFiClientSecure` library for HTTPS communication.

2. **Upload Code:**
   - Connect the ESP8266 to your computer.
   - Select the correct board and port in the Arduino IDE.
   - Upload the code to your ESP8266.

3. **Configure Wi-Fi:**
   - Update the `ssid` and `password` variables in the code with your Wi-Fi credentials.

4. **Set ThingSpeak API:**
   - Sign up for a ThingSpeak account if you don't have one.
   - Create a ThingSpeak channel and generate an API key.
   - Replace the API key in the `weatherApiUrl` with your generated API key.

5. **Wire the Hardware:**
   - Connect the soil moisture sensor's analog output to the `A0` pin of the ESP8266.
   - Connect the relay to the `D1` pin and the water pump to the relay.

## How it Works:
1. **Soil Moisture Monitoring:** The ESP8266 reads the soil moisture value from the analog pin connected to the soil moisture sensor.
2. **Weather Check:** The ESP8266 sends an HTTP request to ThingSpeak to fetch weather data using the ThingSpeak API.
3. **Pump Control:** 
   - If the moisture level is below a set threshold and no rain is detected, the water pump is turned on.
   - If the moisture level is sufficient or rain is detected, the pump is turned off.
4. **Data Update Interval:** The system checks the soil moisture and weather conditions every minute.

## Code Overview:
- **Wi-Fi Setup:** The code connects the ESP8266 to a Wi-Fi network.
- **Moisture Level Check:** The moisture value is checked, and based on the value, the system decides whether to turn the pump on or off.
- **Weather API:** The system requests weather data from the ThingSpeak API and looks for a "Rain" status to determine if it should water the plants.
- **Pump Control:** Based on moisture and weather conditions, the water pump is controlled through the relay module.

## Customization:
- **Moisture Threshold:** Adjust the `moistThreshold` value based on your specific sensor and desired moisture level.
- **API Key:** Replace the API key in the `weatherApiUrl` variable with your own ThingSpeak API key.

## Troubleshooting:
- If the device fails to connect to Wi-Fi, check your network credentials and ensure that your ESP8266 is properly powered.
- If the pump doesn’t turn on/off as expected, verify the connections and the sensor’s readings.

## Future Improvements:
- Add more advanced weather conditions (temperature, humidity) to control watering more intelligently.
- Use an LCD or OLED display to show the moisture level and weather status.
- Implement a mobile app to monitor and control the system remotely.

