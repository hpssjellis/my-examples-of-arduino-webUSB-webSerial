byte incomingByte[1];
int myDelay = 3000;   // non-block delay in milliseconds
unsigned long myStart; 
int serialMessage = 1;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  myStart = millis();   // set delay
  randomSeed(analogRead(A0));  // AO pin on XIAO does not have to be connected to anything

}

void loop() {

    if ( (millis() - myStart ) >= myDelay) {       
       myStart = millis();      //  reset the delay time
       byte myRandByte = (byte)random(0, 8);
       Serial.write(myRandByte); 
     }

  
  if (Serial.available() > 0) {
   // incomingByte[1] = Serial.read();
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

  
