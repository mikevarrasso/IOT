// I, Mike Varrasso, student number 000812269, certify that this material is my original work.
// No other person's work has been used without due acknowledgment
// and I have not made my work available to anyone else.
#include <Arduino.h>

// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6
#define LED_DELAY 10000
#define BLINK_DELAY 125

unsigned long endTime;
unsigned long currentTime;
bool flag = false;
bool btnFlag = true;
bool bPIR;
int buttonState = 1;

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

void alarm()
{
  bPIR = digitalRead(PIN_PIR);

  // This flag will be true if the alarm goes off and the button is not pressed
  if (flag)
  {
    // Keep light on
    digitalWrite(LED_BUILTIN, LOW);
  }

  // If no motion is detected, keep the light off
  else if (!bPIR)
  {
    // Light off
    digitalWrite(LED_BUILTIN, HIGH);
  }

  // If motion is detected...
  else if (bPIR)
  {
    // Get the end time by adding 10 seconds to the current time
    currentTime = millis();
    endTime = currentTime + LED_DELAY;
    flag = true;

    // Blink light until time is up (10 seconds)
    while (currentTime <= endTime)
    {
      buttonState = digitalRead(PIN_BUTTON);
      if (buttonState == 0)
      {
        flag = false;    // Used to keep light on after the blink
        btnFlag = false; // Used to choose if the flag above is triggered or not
        break;
      }

      // Update time
      currentTime = millis();
      // Blink light
      digitalWrite(LED_BUILTIN, LOW);
      delay(BLINK_DELAY);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(BLINK_DELAY);
    }
    if (btnFlag)
      flag = true; // When this flag is true, it will keep the light on after the blinking
  }
}

void loop()
{
  // Call the alarm function
  alarm();
}