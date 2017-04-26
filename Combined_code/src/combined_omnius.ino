/*
Libraries
=====================
*/
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

/*
Sensor Pin Constants
=====================
*/
int Buzzer = 3; //Kevin
int Button = 7; //Kevin
int PIR1 = 6; //David
int PIR2 = 8; //David
int PIR3 = 4;  // David
int Neopixel = 9;//David
int IR_LED = 7; //Kevin
int IR_diode =  3;//Kevin
int TMP36 = 1; //Kevin
int led = 13; // test led to note change on pin 12.
int Light_Sensor = 0; //Kevin
int Mic = 6; //Kevin

// SPi LINES not wokring
// SD card setup

// I2C LINES
//Acceleromter = SDA, SCL

//Neopixel Setup
int numberPixels = 1;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numberPixels, Neopixel, NEO_GRB + NEO_KHZ800);

//Temperature sensor variables:
int tempADC = 0; //analogRead of temperature
float tempV = 0.0; //Temperature in Volts, will be converted to C
float tempC = 0.0; // temperature in celcius
float tempF =0.0;
int V_cc =5;
int CorrectionC = 3; //correction value;

//Accelerometer sensor variables
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
long i_x, i_y, i_z; // these are the initial positions from accelerometer data
long delta_X;
int CountX; // trigger count
long thresholdX = 16500;

//Photoresistor variables:
int LightADC = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Start Combined Code");

  pinMode(led, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(IR_diode, OUTPUT);

  //Acceleromter Start:
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  initializeACC();



  pixels.begin(); // This initializes the NeoPixel.

}

void loop(){
  tmp36Read();
  accRead();
  PhotoresistorRead();
  //delay(1000);
}

void PhotoresistorRead(){
  LightADC = analogRead(Light_Sensor);
  Serial.print(" \t \t Light Value   ");
  Serial.print(LightADC);
  Serial.print("\t");
}

void initializeACC() {
  // get inital values for the accelerometer
  for (int i = 0; i < 10; i++) {
    i_x += Wire.read() << 8 | Wire.read();
    i_x /= 10; //find average
  }
}

int stateChange() {
  //this function checks to see if there is any change.
  //will run at start up, and then will run again each loop/
  //any change from iniital conditions will result in an alarm.
  //initializeACC();
  AcX = Wire.read() << 8 | Wire.read();
  delta_X = abs( i_x - AcX ); //change value
  if (delta_X > thresholdX ) {
    CountX ++;//incriment
    return 1;
  }
  else {
    return 0;
  }
}//end of State Change

void accRead(){
  Wire.beginTransmission(MPU_addr);
 Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
 AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
 Serial.println();
 Serial.print(AcX);
 Serial.print("\t");
 Serial.print(" Delta:   ");
 Serial.print(delta_X);
 Serial.print("\t \tThe trigger Count is: \t");
 Serial.print(CountX);
 AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
 Serial.print(AcY);
 // AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
 // Serial.println("adfadf");
 if (stateChange()) // checks to see if a state has change
 {
   digitalWrite(led, HIGH);
   delay(500);
   digitalWrite(led, LOW);
   delay(500);
   initializeACC();
 }
}


void NeopixelON(int led_index){
  pixels.setPixelColor(led_index, pixels.Color(0,150,0)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void tmp36Read(){
  tempADC = analogRead(TMP36);
  tempV = ((float)tempADC/1023.0)*((float)V_cc); // V_cc is 5v,
  tempC = ((tempV - .5)/ .010) + CorrectionC;
  tempF = tempC * (9.0/5.0) +32.0;
  Serial.println(tempF);
  Serial.print("\t °F");
  Serial.print(tempC);
  Serial.print("\t °C");
//  Serial.println();

}
