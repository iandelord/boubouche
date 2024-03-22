#include <CapacitiveSensor.h>

CapacitiveSensor doigts = CapacitiveSensor(4, 2);


int serialCtrl = 0;

int thresholdT = 2000;
bool recording = false;
bool on = false;
unsigned long prevTime = 0;
unsigned long recTime = 0;

int RED = 5;
int GREEN = 6;
int BLUE = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  
  setLedMode(0);
  
  setLedMode(1);

  prevTime=millis();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  long capValue = doigts.capacitiveSensor(30);
  if(Serial.available()>0){
    serialCtrl = Serial.read();
    Serial.print("got message");
    Serial.println(serialCtrl);
  }
  if(capValue>thresholdT || serialCtrl=="RECORDING"){
    if(!recording){
      recording = true;
      setLedMode(2);
      recTime=millis();
    }
  } else {
    if(recording && millis()-recTime>10000){
      recording = false;
      Serial.println("ENDED");
      setLedMode(1);
    }
  }
}

void setLedMode(int a) {
  switch(a){
    case 0:
      Serial.println("BOOTING");   
      digitalWrite(RED, HIGH);
      for(int i = 0; i<4; i++){
        digitalWrite(GREEN, LOW);
        delay(500);
        digitalWrite(GREEN, HIGH);
        delay(500);
      }
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);    
      Serial.println("BOOTED");  
      break;
    case 1:
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);
      Serial.println("READY");
      break;
    case 2:
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);
      delay(100);
      //Serial.println(millis()); 
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);
      delay(100);
      //Serial.println(millis()); 
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);      
      Serial.println("RECORDING");
      break;
    case 3:
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, HIGH);  
      Serial.println("ERROR");
      break;
  }
}
