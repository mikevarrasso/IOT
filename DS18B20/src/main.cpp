// I Michael Varrasso, 000812269 certify that this material is my own work
// No other persons work has been used without due aknowledgement
// I have not made my work available to anyone else.

#include <Arduino.h>
// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
DeviceAddress address;

void setup()
{
  Serial.begin(115200);
  // Start the DS18B20 sensor
  DS18B20.begin();
  Serial.println("\nTemperature Application");
  // Check for installed sensors address
  if (!DS18B20.getAddress(address, 0))
  {
    Serial.println("\nNo DS18B20 sensors are installed!");
  }
  else
  {
    // Get the address HEX
    String newAddress;
    for (byte b : address)
      newAddress += String(b, HEX);
    Serial.println("\nFound DS18B20 sensor with address: " + newAddress);
  }
}

void loop()
{
  float temp;
  String condition;
  // Ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();
  // Fetch the temperature. We only have 1 sensor, so the index is 0.
  temp = DS18B20.getTempCByIndex(0);

  // Check temperature conditions
  if (DS18B20.getAddress(address, 0))
  {
    if (temp < 10)
      condition = "° C or cold!";
    else if (temp <= 15 && temp >= 10)
      condition = "° C or cool";
    else if (temp <= 25 && temp >= 15)
      condition = "° C or perfect";
    else if (temp <= 30 && temp >= 25)
      condition = "° C or warm";
    else if (temp <= 35 && temp >= 30)
      condition = "° C or hot";
    else
      condition = "° C or too hot!";
    // Print temperature with condition
    Serial.println("Current temperature is: " + String(temp) + condition);
  }

  // Wait 5 seconds
  delay(5000);
}