/**************************************************************************
 
 Modified code from example project from Adafruit
 Edited by Manno Bult
 Stripped OLED demo animations
 Added HC SR04 (distance sensor) code and averaging its readings

 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

// Needed for the OLED display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED's properties
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C     //< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Ultrasonic Distance Sensor stuff. Using the HC SR04
const int trigPin = 9;  
const int echoPin = 10;

// Smoothing parameters (distance sensors _can_ be erratic, Exponential Moving Average (EMA) smoothes that out a bit)
float alpha = .6;           // EMA smoothing factor (0.0 < alpha <= 1.0) 1.0 is no smoothing, 0.0 is max smoothing (flatline)
float smoothedValue = 0.0;  // Initial smoothed value

float duration, distance, smoothedDistance;

/****************
 * Initialize the whole thing
 *
****************/
void setup() 
{
  // to output to the serial monitor ('debug console')
  Serial.begin(9600);

  // SD1306 initialisation
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  // HC SR04 initialisation
  pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

/****************
 the update loop
****************/
void loop() 
{
  
  distance = measureDistance();
  
  // Apply exponential moving average (EMA)
  smoothedDistance = alpha * distance + (1 - alpha) * smoothedDistance;

  DisplayNumber(smoothedDistance);
  
  // Serial.print(distance);
  // Serial.print(" - ");
  // Serial.println(smoothedDistance);

  delay(100);
}

/****************
 Use the HC SR04 to measure distance
****************/
float measureDistance()
{
  digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  return distance;
}

/****************
 draws a number to the OLED
****************/
void DisplayNumber(float val)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  display.println(val);
  
  display.display();
}

/****************
 * To give a sign of life
 * blink the on-board LED (just for testing I guess)
****************/
void blink(int ms)
{
  digitalWrite(13, HIGH);
  delay(ms);
  digitalWrite(13, LOW);
}
