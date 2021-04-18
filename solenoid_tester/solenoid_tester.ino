int count = 0;

void setup() {
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(12, HIGH);
  int buttonState = digitalRead(13);
  if (buttonState == HIGH) {
    count++;
    delay(100);
  }
  delay(10);
}
