///----Libraries---///
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "TSL2561.h"

///---Defines---///

//light sensor
#define RED_PIN 3
#define BLUE_PIN 5
#define GREEN_PIN 6

//moisture sensor
int thresholdUp = 400;
int thresholdDown = 250;
int sensorPin = A0;

#define RED_PINm 11
#define GREEN_PINm 9
#define BLUE_PINm 10

///---Initialization---///
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
TSL2561 tsl(TSL2561_ADDR_FLOAT); 

///---Setup---///
void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PINm, OUTPUT);
  pinMode(GREEN_PINm, OUTPUT);
  pinMode(BLUE_PINm, OUTPUT);
  if (tsl.begin()) 
  {
    Serial.println("Found sensor");
  } 
  else 
  {
    Serial.println("No sensor?");
    while (1);
  } 
  //tsl.enableAutoRange(true);
  tsl.setGain(TSL2561_GAIN_0X); //Avoids sensor saturation
  tsl.setTiming(TSL2561_INTEGRATIONTIME_101MS);
}

void loop(){


  
  String DisplayWords;
  int sensorValue;
  sensorValue = analogRead(sensorPin);
  Serial.print("Water Level: ");
  Serial.println(sensorValue);

  if (sensorValue <= thresholdDown){
    analogWrite(RED_PINm,255);
    analogWrite(GREEN_PINm, 0);
    analogWrite(BLUE_PINm,0);
    DisplayWords = "Dry, Water it!";
    Serial.println(DisplayWords);

  // If the value is not below our thresholdDown value we want to 
  // check if it is above our thresholdUp value, and if it is 
  // change the display words to "Wet, Leave it!":



  } else if (sensorValue >= thresholdUp){
    analogWrite(BLUE_PINm,255);
    analogWrite(GREEN_PINm, 0);
    analogWrite(RED_PINm,0);
    DisplayWords = "Wet, Leave it!";
    Serial.println(DisplayWords);

  // Otherwise if it is inbetween the two values we want it to 
  // the display it had, so if our soil was really wet and drying 
  // the words would only change to "Dry, Water it!" when it got to the lower threshold
  // (thresholdDown), but if it was dry and getting wetter the words
  // would only change to "Wet, Leave it!" when it got to the upper 
  // threshold (thresholdUp_):

  } else {
    analogWrite(GREEN_PINm,255);
    analogWrite(BLUE_PINm, 0);
    analogWrite(RED_PINm,0);
    DisplayWords = "Plant is happy :)";
    Serial.println(DisplayWords);
  }

  delay(1000); //wait for half a second, so it is easier to read
  uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE); //  measure ambient light
  String stringOne = "The luminosity is: " ;
  String stringThree = stringOne + x;
  Serial.println(stringThree); 
  if (x<100)
  {
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    analogWrite(RED_PIN, 255);
    Serial.println("More light!");
    delay(1000);
  }
  else
  {
      unsigned int rgbColour[3];
      Serial.println("So much light yay :D");
      // Start off with red.
      rgbColour[0] = 255;
      rgbColour[1] = 0;
      rgbColour[2] = 0;  

      // Choose the colours to increment and decrement.
      for (int decColour = 0; decColour < 3; decColour += 1) {
        int incColour = decColour == 2 ? 0 : decColour + 1;

        // cross-fade the two colours.
        for(int i = 0; i < 255; i += 1) {
          rgbColour[decColour] -= 1;
          rgbColour[incColour] += 1;
      
          setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
          delay(5);
        }
  }
  delay(1000);
  }
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
 }
