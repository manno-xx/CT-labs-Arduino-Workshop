
#define CAP_PIN 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(CAP_PIN, INPUT);

  digitalWrite(CAP_PIN, HIGH); // Activation of internal pull-up resistor

  digitalWrite(LED_BUILTIN, LOW);
}

void loopx() {
  // put your main code here, to run repeatedly:
  int capValue = digitalRead(CAP_PIN);
  
  digitalWrite(LED_BUILTIN, capValue);

  Serial.println(capValue);

  delay(50);
}
