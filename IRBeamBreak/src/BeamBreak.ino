/*
Code created by Kevin Kuwata
4/10/17
Beam break using a 1 mega ohm resistor as R1 in a voltage divider with an ir photodiode
using a 62ohm reisstor to maximzie current through ir led.

sensing with analog pin 7
*/
int irPin = A4;
int irValue = 0;

int IR_transistor = 7; //when I get around to it this will control the transistor to swtich the IR light

void setup(){
  pinMode(irValue,  OUTPUT);
  Serial.begin(115200);
  Serial.println("begin.");
}


void loop(){
  irValue = analogRead(irPin );
  Serial.println(irValue);
  delay(100);
}
