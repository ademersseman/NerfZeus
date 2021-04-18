void setup() {
  pinMode(6, OUTPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(4) == 1) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
}
