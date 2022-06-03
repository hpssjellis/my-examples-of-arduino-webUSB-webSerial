byte incomingByte[1];

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int serialMessage = Serial.parseInt();
    if(serialMessage == 1) {
      Serial.println("LED On");
      digitalWrite(LED_BUILTIN, LOW);
    } else if(serialMessage == 0) {
      Serial.println("LED Off");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}
