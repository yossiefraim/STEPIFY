#include <SoftwareSerial.h>
#include "nRF24L01.h"        // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define StripLedPIN 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, StripLedPIN, NEO_GRB + NEO_KHZ800);
int ReceivedMessage[1] = {000};         // Used to store value received by the NRF24L01
RF24 radio(9,10);                      // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO
const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 
int stepAchieved = 0;
int LedsInterval = 1;
void setup()
{
  Serial.begin(9600);
  radio.begin();                  // Start the NRF24L01
  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive
  radio.startListening();       // Listen to see if information received

  strip.begin();
  strip.setBrightness(64);
  strip.setPixelColor(10,50,205,50);
  strip.show(); 
}

void loop(void)
{
  while (radio.available())
  {
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
    stepAchieved += 10;
    Serial.print("StepAceived = ");
    Serial.println(stepAchieved);

    if(stepAchieved < 101)
    {
      turnOnStrip(LedsInterval,255,0,0);
    }
     if(stepAchieved < 201 && stepAchieved > 100)
    {
      turnOnStrip(LedsInterval,255,255,0);
    }
     if(stepAchieved < 301 && stepAchieved > 200)
    {
      turnOnStrip(LedsInterval,0,255,0);
    }
    if(stepAchieved == 300)
    {
      Serial.println("Daily Steps Reached");
      blinkLed(5,10,0, 255, 0);
      turnOffStrip();
      stepAchieved = 0;
    }
    LedsInterval++;
     if(LedsInterval == 11)
      {
        LedsInterval = 1;
      }
    delay(10);
  }
}
void turnOnStrip(int howMany,int red, int green, int blue)
{
    for(int i=0;i<howMany;i++)
  {
      strip.setPixelColor(i, red, green, blue);
      strip.show();
      delay(100);
  }
}
void turnOffStrip()
{
  for(int i=0;i<10;i++)
  {
      strip.setPixelColor(i, 0, 0, 0);
      strip.show();
      delay(100);
  }
}
void blinkLed(int _count,int howMany,int red, int green, int blue)
{
  for(int i=0;i<_count;i++)
  {
    turnOnStrip(howMany,red,green,blue);
    turnOffStrip();
  }
}

