
#define CAP_PIN 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(CAP_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int capValue = digitalRead(CAP_PIN);

  digitalWrite(LED_BUILTIN, capValue);

  Serial.println(capValue);

  delay(50);
}
