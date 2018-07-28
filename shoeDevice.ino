// include

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define SwitchPin 8                         // Arcade switch is connected to Pin 8 on NANO
int backFsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int frontFsrPin = 2;
int BACKfsrReading,FRONTfsrReading;   
int stepsAchieved = 0;
bool flagBetweenSensors = false;
const int countToAlert = 10;

int SentMessage[1] = {000};               // Used to store value before being sent through the NRF24L01
RF24 radio(9,10);                        // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO
const uint64_t pipe = 0xE6E6E6E6E6E6;   // Needs to be the same for communicating between 2 NRF24L01 
void setup() 
{
  Serial.begin(9600);
  pinMode(SwitchPin, INPUT_PULLUP);     // Define the arcade switch NANO pin as an Input using Internal Pullups
  digitalWrite(SwitchPin,HIGH);         // Set Pin to HIGH at beginning
  radio.begin();                        // Start the NRF24L01
  radio.openWritingPipe(pipe);          // Get NRF24L01 ready to transmit
}
void loop(void) 
{
 // test();
  stepsCounter ();

   if(stepsAchieved == countToAlert)
   {
      stepsAchieved = 0;
      sendCount(countToAlert);
   }
} 

int stepsCounter ()
{
  BACKfsrReading = analogRead(backFsrPin);  
 // FRONTfsrReading = analogRead(frontFsrPin);
  
  if(BACKfsrReading > 800)
  {
   // flagBetweenSensors = true;
      Serial.print("Back reading = ");
      Serial.print(BACKfsrReading);   
      stepsAchieved++;
      delay(1200);
  }
//    if(FRONTfsrReading > 800 && flagBetweenSensors)
//  {
//    flagBetweenSensors = false;
//    stepsAchieved++;
//  }
  return stepsAchieved;
}
void sendCount(int _countToAlert)
{
    SentMessage[0] = '1';
    radio.write(SentMessage, 1);          // Send value through NRF24L01
    Serial.println("sent");
    Serial.println(SentMessage[0]);
}
//void test()
//{
//  BACKfsrReading=0;
//   BACKfsrReading = analogRead(backFsrPin);  
//   Serial.print("Back reading = ");
//   Serial.print(BACKfsrReading);     
//   Serial.println("");
//   delay(2000);
//   FRONTfsrReading=0;
//   FRONTfsrReading = analogRead(frontFsrPin);  
//   Serial.print("Front reading = ");
//   Serial.print(frontFsrPin);     
//   Serial.println("");
//   delay(2000);
//}

