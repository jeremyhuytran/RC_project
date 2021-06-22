#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#define LED_PIN 2
#define CE_PIN    9
#define CS_PIN    10
int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
RF24 radio(CE_PIN,CS_PIN); // NRF24L01 SPI pins. Pin 9 and 10 on the Nano

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup(void)
{
    Serial.begin(9600);
  radio.begin(); // Start the NRF24L01
  
  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive
  
  radio.startListening(); // Listen to see if information received
  
  pinMode(LED_PIN, OUTPUT); 
  delay(200);
  Serial.println("starting.................");
}

void loop(void)
{
  while (radio.available())
  {
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

    if (ReceivedMessage[0] == 1) // Indicates switch is pressed
    {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("HIGH");
      
    }
    else
    {
       digitalWrite(LED_PIN, LOW);
        Serial.println("LOW");
    }
    delay(20);
   }

//      digitalWrite(LED_PIN, HIGH);
//      Serial.println("HIGH");
//      delay(2000);
//       digitalWrite(LED_PIN, LOW);
//        Serial.println("LOW");
//      delay(2000);
}
