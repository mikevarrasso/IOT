// Lab #3
// I Michael Varrasso, 000812269 certify that this material is my own work.
// No other persons work has been used without due aknowledgement.
// I have not made my work available to anyone else.

#include <Arduino.h>
// Save state of button
int buttonState = 0;

void setup()
{
  // Configure the USB serial monitor
  Serial.begin(115200);
  // Input (Button)
  pinMode(D5, INPUT_PULLUP);
  // Output (LED)
  pinMode(D4, OUTPUT);
}

void loop()
{
  // Get the value of the analog input
  int iVal = analogRead(A0);
  // Read push button input...
  int iButton = digitalRead(D5);

  // Output to the LED
  if (iButton == 1)
  {
    // Turn LED off...
    digitalWrite(D4, HIGH);
  }
  else
  {
    // Turn LED on...
    // Adjust the brightness of the LED light
    analogWrite(D4, iVal);
  }
}
