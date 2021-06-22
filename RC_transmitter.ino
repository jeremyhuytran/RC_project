#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24 // provide macros
#include "RF24.h"
#include "SPI.h"

#define SwitchPin 2 
#define CE_PIN    9
#define CS_PIN    10
int SentMessage[1] = {000}; 
RF24 radio(CE_PIN,CS_PIN); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup()
{
  pinMode(SwitchPin, INPUT_PULLUP); 
//  digitalWrite(SwitchPin,HIGH); 
  Serial.begin(9600);
  
  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop()
{
  if (digitalRead(SwitchPin) == LOW)    // If switch is pressed
  { 
      SentMessage[0] = 1;
      radio.write(SentMessage, 1);      // Send pressed data to NRF24L01
      Serial.println(" sent LOW");
  }
  else 
  {
      SentMessage[0] = 0;
      radio.write(SentMessage, 1);      // Send idle data to NRF24L01
      Serial.println(" sent HIGH");
  }
  delay(100);
}
