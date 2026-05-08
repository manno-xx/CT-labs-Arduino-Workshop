/*

  Modified from AnalogReadSerial example from Arduino

  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/

#include <Servo.h>

#define xPin A0
#define yPin A1
#define servoPin 9

Servo myServo;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myServo.attach(servoPin);
}

// the loop routine runs over and over again forever:
void loop() 
{
  // read the input on analog pin 0:
  int xMovement = analogRead(xPin);
  int yMovement = analogRead(yPin);

  int angle = map(xMovement, 0, 1024, 0, 180);
  myServo.write(angle);

  // print out the value you read:
  Serial.print(xMovement);
  Serial.print(",");
  Serial.println(yMovement);
  
  delay(10);  // delay in between reads for stability
}
