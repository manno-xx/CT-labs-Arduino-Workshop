// Using Joy-IT KY-012 (piezo) and KY-004 (button)

int button = 10; // Declaration of the sensor input pin
int value;       // Temporary variable

const int piezoPin = 9;

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
