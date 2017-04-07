
/*
Base code from
// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain



****
Changes made by Kevin Kuwata 3/27/17
made trigger conditions based on data collected by JohnChi's code.

Future ideas to chagne code:
Auto calibrate function
  develope a way to save a integer to EEProm,
  Everytime an event is triggered increase threshold by 1.
  if threshold doesn't change in 10 mins save to eeprom.

Better triggering system
  Instead of trigering on just a single value being larger than the required delta
  let us try to trigger on 2 events. so normally we will trigger based on on
  1 event, and then we will see if we are changing values within a short period
  if we are then we know its a real trigge rand to trigger.

  this way the sensitivity is not as crucial, but more based on any changes that happen
  more than once. we can even reduce the threshold because then a vibration won't set it off
  but multiple vibrations consecutively wil. 


WIRING SETUP:
-----Arduino -----
Led is digital pin 12
----- GY-521 ----- > Arduino
SDA - Analog 4
SCL- Analog 5
5V to VCC
gnd to Gnd
INT > Gnd


*/
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int i_x, i_y, i_z; // these are the initial positions from accelerometer data
int delta_X;
int CountX; // trigger count

int led = 12; // test led to note change on pin 12.

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);

pinMode(led, OUTPUT);
digitalWrite(12, HIGH);
delay(250);
digitalWrite(12, LOW);

initializeACC();

delay(5000); // So I can walk away!

}

void initializeACC(){
  // get inital values for the accelerometer
  for(int i=0; i<10; i++){
      i_x += Wire.read() <<8|Wire.read();
      i_x /= 10; //find average
  }
}

int stateChange(){
//this function checks to see if there is any change.
//will run at start up, and then will run again each loop/
//any change from iniital conditions will result in an alarm.
//initializeACC();
AcX=Wire.read()<<8|Wire.read();
delta_X =abs( i_x - AcX ); //change value

if(delta_X > 350 ){
  CountX ++;//incriment
  return 1;
}
else{
  return 0;
}


}//end of State Change

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
   AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
   Serial.println(AcX);
   Serial.print("\t");
   Serial.print(" Delta:   ");
   Serial.println(delta_X);
   Serial.print("\t \tThe trigger Count is: \t");
   Serial.println(CountX);
  // AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  // AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  if(stateChange()) // checks to see if a state has change
  {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
    initializeACC();
  }
}


/*
Extra Stuff for getting and displaying values.
Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
Serial.print("AcX = "); Serial.print(AcX);
Serial.print(" | AcY = "); Serial.print(AcY);
Serial.print(" | AcZ = "); Serial.print(AcZ);
Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
Serial.print(" | GyX = "); Serial.print(GyX);
Serial.print(" | GyY = "); Serial.print(GyY);
Serial.print(" | GyZ = "); Serial.println(GyZ);

*/
