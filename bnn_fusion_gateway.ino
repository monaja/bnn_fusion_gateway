//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>
#include <DHT11.h>

// Define pins
#define CE_PIN 7
#define CSN_PIN 8

// Create RF24 radio object
RF24 radio(CE_PIN, CSN_PIN);
RF24Network network(radio);
const uint16_t node_id = 00;
const uint16_t base_node_id =00; 
 
 
struct  Data
{
  float temp = -9999.0;
  float humid = -9999.0;
  int moist = -9999;
  int relay = -9999;
  /* data */
};

Data pay_load; 

void setup() {
  Serial.begin(9600); 
  radio.begin();
  network.begin(90, node_id);  
}
void loop() {
  network.update();
  //Send message to receiver 
  while(network.available()){
    Serial.println("Incoming network data.");
    RF24NetworkHeader header;
    network.read(header, &pay_load, sizeof(pay_load));
    Serial.println(header.from_node);
    Serial.println(pay_load.temp);
    Serial.println(pay_load.humid);
    Serial.println(pay_load.moist);
    Serial.println(pay_load.relay);    
  }
  //Serial.println("Another one.");
}