

#include <VirtualWire.h>  //Library Required
#include <LiquidCrystal.h>


#define relayOutVcc A0
#define relayOutPin A2

const int lv=2,rs = 4, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int RX_PIN = 11;// Tell Arduino on which pin you would like to receive data NOTE should be a PWM Pin
int RX_ID = 3;// Recever ID address 
int TX_ID;



struct roverRemoteData //Data Structure 
{
int    TX_ID;      // Initialize a storage place for the incoming TX ID  
int    Sensor1Data;// Initialize a storage place for the first integar that you wish to Receive 
int    Sensor2Data;// Initialize a storage place for the Second integar that you wish to Receive
int    Sensor3Data;// Initialize a storage place for the  Third integar that you wish to Receive
int    Sensor4Data;// Initialize a storage place for the Forth integar that you wish to Receive

};

void setup() {


              pinMode(relayOutPin, OUTPUT);
              lcd.begin(8, 2);
              lcd.print("Pls Wait");
              Serial.begin(9600);// Begin Serial port at a Buad speed of 9600bps 
              vw_setup(2000);// Setup and Begin communication over the radios at 2000bps( MIN Speed is 1000bps MAX 4000bps)
              vw_set_rx_pin(RX_PIN);// Set RX Pin 
              vw_rx_start(); 
              pinMode(12, OUTPUT);
              digitalWrite(12, HIGH);    
              }  
void loop()
{
      struct roverRemoteData receivedData;
      uint8_t rcvdSize = sizeof(receivedData);//Incoming data size 
      vw_wait_rx();// Start to Receive data now 
      digitalWrite(relayOutVcc, HIGH);
      lcd.clear();
      if (vw_get_message((uint8_t *)&receivedData, &rcvdSize)) // Check if data is available 
{
  if (receivedData.TX_ID == RX_ID) //Check if the radio signal recieved matches the ID of the Reciever
    { 
      // If data was Recieved print it to the serial monitor.
         Serial.println("------------------------New MSG-----------------------");
         Serial.print("TX ID:");
         Serial.println(TX_ID);
         Serial.print("Sensor1Data:");
         Serial.println(receivedData.Sensor1Data);
         Serial.print("Sensor2Data:");
         Serial.println(receivedData.Sensor2Data);
         Serial.print("SensorData3:");
         Serial.println(receivedData.Sensor3Data);
         Serial.print("SensorData4:");
         Serial.println(receivedData.Sensor4Data);
           if((receivedData.Sensor2Data)==5){
                 lcd.setCursor(0,0);
                 lcd.print("HMT ON");
            if  ((receivedData.Sensor1Data)<400){
                lcd.setCursor(0,1);
                lcd.print("- DRIVE");
                digitalWrite(relayOutPin, LOW);
                  }
            else { 
                lcd.setCursor(0,1);
                lcd.print("- DRUNK?");
                digitalWrite(relayOutPin, LOW);



            }
            
            }
          else {
            lcd.setCursor(0,0);
            lcd.print("WEAR");
            lcd.setCursor(0,1);
            lcd.print("HELMET");
            digitalWrite(relayOutPin, LOW); }
         Serial.println("-----------------------End of MSG--------------------");
        } 
      else
        { 
Serial.println(" ID Does not match waiting for next transmission ");
        lcd.setCursor(0,0);
        lcd.print("NO  HEL");
        lcd.setCursor(0,1);
        lcd.print("MET");
        
        } 
      } 
    }

