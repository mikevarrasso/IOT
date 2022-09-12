#include <Arduino.h>
//Mike Varrasso 000812269

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Serial.println("\n\nHello, World!");
  Serial.println("\nMike Varrasso (000812269)");


  Serial.println("\nESP8266 Chip ID: " + String(ESP.getChipId()) + "\nFlash Chip ID: " + String(ESP.getFlashChipId()));
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Time: ");
  long myTime = millis();

  Serial.println(myTime);
  delay(2000);    
}