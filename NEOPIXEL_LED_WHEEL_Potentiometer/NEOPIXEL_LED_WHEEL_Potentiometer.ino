/****
 * Adaptation of an Adafrui NEOpixel strandtest wheel example
 *
 * Potentiometer sets the number of pixeld lit up as well. as the color
 *
****/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// NeoPixel stuff
#define PIN 6
#define LED_COUNT 16

// the pot. meter
#define POTENTIOMETER_PIN A0

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() 
{
  Serial.begin(9600);

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(20);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  // Reading the potentiometer
  int raw = analogRead(POTENTIOMETER_PIN);
  
  // mapping how many pixels should light up
  int pixCount = map(raw, 0, 1024, 0, LED_COUNT);
  // and in what hue
  long hue = map(raw, 0, 1024, 0, 65536 * .33);
  
  // calculate RGB value of it 
  uint32_t color = strip.ColorHSV(hue);

  // clear the strip
  strip.clear();
  
  // lite 'm up!
  for(uint16_t i = 0; i < pixCount+1; i++) 
  {
    strip.setPixelColor(i, color);
  }

  strip.show();

  //Serial.print(raw);
  //Serial.print(" - ");
  //Serial.print(pixCount);
  //Serial.print(" - ");
  //Serial.println(hue);
}
