byte incomingByte[1];
int myDelay = 2000;   // non-block delay in milliseconds
unsigned long myStart; 
bool  mySwitch = false; 
int serialMessage = 1;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  myStart = millis();   // set delay

}

void loop() {

    if ( (millis() - myStart ) >= myDelay) {       
       myStart = millis();      //  reset the delay time
       Serial.write(serialMessage); 
     }

  
  if (Serial.available() > 0) {
    serialMessage = Serial.parseInt();
    if(serialMessage == 1) {
      Serial.println("LED On");
      digitalWrite(LED_BUILTIN, LOW);
    } else if(serialMessage == 0) {
      Serial.println("LED Off");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}

  

