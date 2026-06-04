/*
  Using the RCWL-0516 Microwave Radar

  Adaptation by Manno Bult based on source below
  Adaptation mainly involves the running on the UNO R4 and using its LED matrix for movement indication
  Do read the link below regarding issue 57 about sensitivity (or experienced lack thereof)

  see also: https://github.com/jdesbonnet/RCWL-0516
  and: https://github.com/jdesbonnet/RCWL-0516/issues/57 (mainly about the sensitivity of the sensor)

  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/arduino-rcwl-0516/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

//If you're using the built-in LED for testing, remember that it works with inverted logic
//(HIGH=LOW, and LOW=HIGH)
int led = 13;                // the pin that the LED is attached to
int sensor = 12;              // the pin that the sensor is attached to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

// Matrix related variables
int blinkInterval = 1000;
unsigned long nextBlink = 0;

uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void setup() 
{
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial

  matrix.begin();

  nextBlink = millis() + blinkInterval;
}

void loop()
{  
  unsigned long now = millis();
  
  // Let the top-left LED blink (more or less) independent of other timing (just to show the sketch is running)
  if(now > nextBlink)
  {
    blink();
    matrix.renderBitmap(frame, 8, 12);
    nextBlink = now + blinkInterval;
  }

  val = digitalRead(sensor);   // read sensor value

  if (val == HIGH) 
  {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    
    if (state == LOW) 
    {
      ToggleMovementIndicator(1);
      matrix.renderBitmap(frame, 8, 12);
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else 
  {
    digitalWrite(led, LOW); // turn LED OFF
    
    if (state == HIGH)
    {
      ToggleMovementIndicator(0);
      matrix.renderBitmap(frame, 8, 12);
      Serial.println("Motion stopped!");
      state = LOW;       // update variable state to LOW
    }
  }
}

// toggle the upper-left pixel of the matrix
void blink()
{
  frame[0][0] = !frame[0][0];
}

void ToggleMovementIndicator(int state)
{
  for(int y = 2; y < 6; y++)
  {
    for(int x = 4; x < 8; x++)
    {
      frame[y][x] = state;
    }
  }
}



