///----Libraries---///
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "TSL2561.h"

///---Defines---///
//#define PIXEL_PIN 6  
//#define PIXEL_COUNT 1

#define RED_PIN 3
#define BLUE_PIN 5
#define GREEN_PIN 6

///---Initialization---///
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
TSL2561 tsl(TSL2561_ADDR_FLOAT); 

///---Setup---///
void setup() {
  Serial.begin(9600);
  //strip.begin(); // Neopixel Setup
  //strip.show(); // Initialize all pixels to 'off'
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
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
  //for (time<
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //delay(2000);
  //colorWipe(strip.Color(0, 0, 255), 50);//Blue
  //delay(2000);
  //colorWipe(strip.Color(255, 255, 0), 50); //Yellow
  //delay(2000);
  //colorWipe(strip.Color(0, 0, 0), 50);

  uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE); //  measure ambient light
  String stringOne = "The luminosity is: " ;
  String stringThree = stringOne + x;
  Serial.println(stringThree); 
  if (x<170)
  {
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    analogWrite(RED_PIN, 255);
    delay(1000);
  }
  else
  {
      unsigned int rgbColour[3];

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
