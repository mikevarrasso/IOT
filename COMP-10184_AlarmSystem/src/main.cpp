// I, Mike Varrasso, student number 000812269, certify that this material is my original work.
// No other person's work has been used without due acknowledgment
// and I have not made my work available to anyone else.

// Assignment #1: Alarm System
// * * STAGE 5 COMPLETED * *
#include <Arduino.h>

// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6
#define LED_DELAY 10000
#define BLINK_DELAY 125
unsigned long endTime;     // Used for the 10 second alarm loop
unsigned long currentTime; // Used for the 10 second alarm loop
bool flag = false;         // This flag is used to keep the light on after the 10 second alarm
bool btnFlag = true;       // This flag will be used to keep track of button presses
bool bPIR;                 // Used for motion detection
bool disabled = false;     // Disabled mode for alarm flag
int buttonState;           // Used to track the state of the button press

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);
  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);
  // PIR sensor is an INPUT
  pinMode(PIN_PIR, INPUT);
  // Button is an INPUT
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

// This function is used to blink the LED light used in the alarm
void blinkLight()
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(BLINK_DELAY);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(BLINK_DELAY);
}

void alarm()
{
  bPIR = digitalRead(PIN_PIR);
  // If the alarm is disabled, keep the light off until another button press
  if (disabled)
  {
    // Since the alarm is in disabled mode, digitalWrite HIGH to keep light off
    digitalWrite(LED_BUILTIN, HIGH);
    buttonState = digitalRead(PIN_BUTTON);
    if (buttonState == 0) // If the button is pressed reset the alarm
    {
      Serial.print("\nALARM RESET");
      disabled = false;
      delay(300);
    }
  }

  // Keep light on after the 10 seconds of blinking
  else if (flag)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // If no motion is detected, keep the light off
  else if (!bPIR)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  // If motion is detected...
  else if (bPIR)
  {
    // Get the end blink time by adding 10 seconds to the current time
    Serial.print("\nMOTION DETECTED: Alarm will sound in 10 seconds...");
    currentTime = millis();
    endTime = currentTime + LED_DELAY;
    flag = true;

    // Blink light until time is up (10 seconds)
    while (currentTime <= endTime)
    {
      buttonState = digitalRead(PIN_BUTTON);
      // If the button is clicked while led is blinking, disable the alarm
      if (buttonState == 0)
      {
        flag = false;    // Used to keep light on after the blink
        btnFlag = false; // Used to choose if the flag above is triggered or not
        disabled = true;
        Serial.print("\nALARM DISABLED");
        delay(300);
        break;
      }
      currentTime = millis(); // Update current time
      blinkLight();
    }

    if (btnFlag) // If the button was not pressed set the flag to true (used to keep light on)
    {
      Serial.write("\nAlarm not reset in time... INTRUDER!!!!");
      flag = true; // When this flag is true, it will keep the light on after the blinking
    }
  }
}

void loop()
{
  // Call the alarm function
  alarm();
}