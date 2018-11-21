#include <VirtualWire.h> // Library Required
const int AOUTpin=A0;//the AOUT pin of the alcohol sensor goes into analog pin A0 of the arduino
const int aVcc=A3;//the DOUT pin of the alcohol sensor goes into digital pin D8 of the arduino

int alcoLimit;
int alcoValue;
int TX_PIN = 3;// Tell Arduino on which pin you would like to Transmit data NOTE should be a PWM Pin
int TX_ID = 3; // Transmitter ID address
int switchVcc =8;
int switchPin=9;
int switchData;

struct roverRemoteData// Data Structure 
{
int    TX_ID;      // Initialize a storage place for the outgoing TX ID
int    Sensor1Data;// Initialize a storage place for the first integar that you wish to Send 
int    Sensor2Data;// Initialize a storage place for the Second integar that you wish to Send
int    Sensor3Data;// Initialize a storage place for the Third integar that you wish to Send
int    Sensor4Data;// Initialize a storage place for the Forth integar that you wish to Send


};

void setup() {
              pinMode(aVcc, OUTPUT);
              digitalWrite(aVcc, HIGH);
              Serial.begin(9600);// Begin Serial port at a Buad speed of 9600bps 
              vw_setup(2000);// Setup and Begin communication over the radios at 2000bps( MIN Speed is 1000bps MAX 4000bps)
              vw_set_tx_pin(TX_PIN);// Set Tx Pin
              pinMode(2, OUTPUT);
              digitalWrite(2, HIGH);
              pinMode(switchVcc, OUTPUT);
              digitalWrite(switchVcc, HIGH);
              pinMode(switchPin, INPUT);
              
              }
void loop()
{ digitalWrite(aVcc, HIGH);
  struct roverRemoteData payload;// In this section is where you would load the data that needs to be sent.
  
  // If you want to read a analog pin and transmit its value you can do it as follows by removing the "//" 
  payload.TX_ID = TX_ID; // Set the Radio Address 
  alcoValue= analogRead(AOUTpin);
  payload.Sensor1Data =alcoValue;// analogRead(Sensor1Pin);
  if((digitalRead(switchPin)==HIGH)){switchData=5;}
  else switchData=0;
  payload.Sensor2Data =switchData;// analogRead(Sensor2Pin);
  payload.Sensor3Data =1;// analogRead(Sensor3Pin);
  payload.Sensor4Data =1;// analogRead(Sensor4Pin);
 
  
  
  vw_send((uint8_t *)&payload, sizeof(payload)); // Send the data 
  vw_wait_tx();// Wait for all data to be sent 
  

}

