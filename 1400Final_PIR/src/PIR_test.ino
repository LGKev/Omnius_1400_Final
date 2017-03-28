/*
Created 73/28/17 7:46 am

Kevin Kuwata

Arduino Nano and Panosonic PIR sensor

Wiring
PIR -> Arduino
pin (1) gnd -> gnd
pin(2) Signal -> A1
pin(3) VCC -> 5v
*/


/* ===== constants ===== */
int led =12; //inidcator led for trigger of PIR
int pirPin = A1;
int pirVal = 0;
unsigned long timeThreshold = 500; //milliseconds we want it to be triggered for more than 2 seconds
unsigned long lastTriggered = 0; //start with 0.
unsigned long timeTriggered = 0; //start with 0.
int trigCount = 0; // count how many events were triggered

int pirThreshold = 512; // half of 1024


void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  Serial.println("Begin.");
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}

int triggerTime()
{
  timeTriggered = millis();
  if(timeTriggered - lastTriggered > timeThreshold)
  {
    lastTriggered = timeTriggered;
    return 1;
  }
  return 0;
}
//
// int triggerCount(){
//   if(triggerCount())
// }



void loop(){

pirVal = analogRead(pirPin);

if(pirVal > pirThreshold)
  {
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  trigCount ++;
  }



}
