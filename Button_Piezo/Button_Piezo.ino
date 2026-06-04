// Using Joy-IT KY-012 (piezo) and KY-004 (button)

int button = 10; // Declaration of the sensor input pin
int value; // Temporary variable

const int piezoPin = 9;


// Smoothing parameters (distance sensors _can_ be erratic, Exponential Moving Average (EMA) smoothes that out a bit)
float alpha = .6;           // EMA smoothing factor (0.0 < alpha <= 1.0) 1.0 is no smoothing, 0.0 is max smoothing (flatline)
float smoothedValue = 0.0;  // Initial smoothed value

float duration, distance, smoothedDistance;

void setup () {
  pinMode(button, INPUT); // Initialization sensor pin
  digitalWrite(button, HIGH); // Activation of internal pull-up resistor

  pinMode(piezoPin, OUTPUT);

  Serial.begin(9600); // Initialization of the serial monitor
}
  
void loop () {
  // The current signal at the sensor is read out.
  value = digitalRead(button);

  if(value == LOW)
  {
    digitalWrite(piezoPin, HIGH);
  }
  else
  {
    digitalWrite(piezoPin, LOW);
  }

  delay(50);
}
