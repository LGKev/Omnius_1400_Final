// neo pixel single color
//https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library
#include <Adafruit_NeoPixel.h>
#define PIN 8

#define NUMPIXELS 1 //was able to drive all 400 and worked.

int blinkd = 0;
volatile long lastDebounceTime = 0;
int flashSpeed =100;
int r=0; int g=0;
 int b=0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  //attachInterrupt(1, blinkdf, CHANGE);//numbers https://www.arduino.cc/en/Reference/AttachInterrupt
}


void loop() {
//slowFade3(r,g,b);
delayMicroseconds(500);
digitalWrite(10, HIGH);
delayMicroseconds(500);
digitalWrite(10, LOW);
Serial.println(analogRead(A6));
  while(analogRead(A6)>500){
    digitalWrite(12, LOW);
    delay(10);
  }
  Serial.println(analogRead(A7));

  pixels.setPixelColor(0, pixels.Color(0,255,0));
}

void slowFade3(int r, int g, int b){
  //  r++;
  while(1){
    r++;
    pixels.setPixelColor(0, pixels.Color(r, g,  b));
    delay(10);
    if(r >100){
        pixels.setPixelColor(0, pixels.Color(r, g,  b));
        g++;
            }
    if(g>100){
      b++;
    }
    pixels.show();
  }

}

void slowFade2(){

//first pixel is indexed at 0. Frst arguement is the pixel number not what pin
for(int r = 0; r<=2; r++){
  int g=0, b=0;
  pixels.setPixelColor(0, pixels.Color(r,g,b)); //led 0,1,2,3,4,5,6
  delay(50);
  if(r>10){
      pixels.setPixelColor(0, pixels.Color(r,g,b));
      g++;
  }
  if(g>10){
      pixels.setPixelColor(0, pixels.Color(r,g,b));
  }
  g++;
  r--;

}
  pixels.show();
}
void flasher(){

  for (int j = 0; j <= 1; j++) {

    delay(flashSpeed);
  }
    pixels.show();

    for (int j = 0; j <= NUMPIXELS; j++) {
    pixels.setPixelColor(j, pixels.Color(0, 0, 255 )); //led 0,1,2,3,4,5,6
    delay(10);
        pixels.setPixelColor(j-1, pixels.Color(0, 0, 0 )); //led 0,1,2,3,4,5,6
  pixels.show();
    delay(flashSpeed);
  }
    pixels.show();
}



void setGreen()
{
  for (int j = 0; j <= NUMPIXELS; j++) {
    pixels.setPixelColor(j, pixels.Color(0, 255, 0 )); //led 0,1,2,3,4,5,6
  }
}

void setRandom()
{
  for (int j = 0; j <= NUMPIXELS; j++) {
    pixels.setPixelColor(j, pixels.Color(random(0, 200), random(100, 200), random(0, 200) )); //led 0,1,2,3,4,5,6
  }
}

void chase(uint32_t c) {
  for (uint16_t i = 0; i < pixels.numPixels() + 4; i++) {
    pixels.setPixelColor(i  , c); // Draw new pixel
    pixels.setPixelColor(i - 4, 0); // Erase pixel a few steps back
    pixels.show();
    delay(flashSpeed);
  }
}

void blinkdf()
{
  if ((millis() - lastDebounceTime) > 250)
  {
    lastDebounceTime = millis();
    blinkd++;

    if (blinkd > 3)
    {
      blinkd = 0;
    }
  }

}
