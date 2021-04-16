void setup() {
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(4);
  if (buttonState == HIGH) {
    digitalWrite(5, HIGH);
  }
  delay(10);
}
