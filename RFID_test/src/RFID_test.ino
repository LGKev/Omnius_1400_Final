



int ss = 10;
int mosi = 11;
int miso = 12;
int sck = 13;

void setup()
{
  pinMode(ss, OUTPUT);
  pinMode(mosi, OUTPUT);
  pinMode(miso, INPUT);
  pinMode(sck, OUTPUT);


  Serial.begin(9600);
  Serial.println("start");

  //set slave
  digitalWrite(ss, HIGH); //to pick the slave correctly. LOW to enable the slave

}

unsigned int ReadBit(){
    unsigned int byte_in = 0;
  //turn on slave to listen
  for(int bit = 0x80; bit; bit >>=1){ // start with a 1 at the begining shift, go until bit (some terminator?) then shift bit 1 place to the right.
      Serial.print("bit:  ");
      Serial.println(bit);
  digitalWrite(ss, LOW);
  delay(50); //50 micros apparently you only need 25ns. but lets do it slow.
  digitalWrite(sck, HIGH);
  if(digitalRead(miso) == HIGH){
    Serial.println("We got DATA");
    //theres data!
    byte_in |= bit;
  }
  delay(50);
  digitalWrite(sck, LOW);
    } //end of for loop, which loops over all bits into the byte
    return byte_in;
}


unsigned byteREAD = 0123456;

void loop(){
  byteREAD = ReadBit();
  Serial.println(byteREAD);

}
