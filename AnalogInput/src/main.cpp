#include <Arduino.h>

// I Michael Varrasso, 000812269 certify that this material is my own work
// No other persons work has been used without due aknowledgement
// I have not made my work available to anyone else.

float mapfloat(float x, float inMin, float inMax, float outMin, float outMax)
{
  return (float)(x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

String tempFloat(float x, float inMin, float inMax, float outMin, float outMax)
{
  float temp = (float)(x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;

  if (temp < 10)
  {
    return(String(temp) + " deg. C, which is cold!");
  }
  else if (temp <= 15 && temp >= 10) 
  {
    return(String(temp) + " deg. C, which is cool");
  }
  else if (temp <= 25 && temp >= 15) 
  {
    return(String(temp) + " deg. C, which is perfect");
  }
  else if (temp <= 30 && temp >= 25) 
  {
    return(String(temp) + " deg. C, which is warm");
  }
  else if (temp <= 35 && temp >= 30) 
  {
    return(String(temp) + " deg. C, which is hot");
  }
  else {
    return(String(temp) + " deg. C, which is too hot!");
  }
  
}

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);
}
void loop()
{
  int iVal;

  // read digitized value from the D1 Mini's A/D convertor
  iVal = analogRead(A0);

  float digitalVal = mapfloat(iVal, 0, 1023, 0, 3.3);
  String tempVal = tempFloat(iVal, 0, 1023, 0, 50);
  // print value to the USB port
  Serial.println("Digitized Value of " + String(iVal) + " is equal to an Analog Voltage = " + digitalVal + "V.");
  Serial.println("Digitized output of " + String(iVal) + " is equal to a temperature input of " + tempVal);
  // wait 2 seconds
  delay(2000);
}
