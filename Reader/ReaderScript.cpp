/*
*/
 
#include <SoftwareSerial.h>
 
SoftwareSerial SoftSerial(2, 3);
unsigned char buffer[64];      
int RedLed = {8};   
int GreenLed = {4};
int count = 0;       
int LedTime(50);          
 
void setup()
{
    SoftSerial.begin(9600);   
    Serial.begin(9600);    
    pinMode(6, OUTPUT);
    pinMode(RedLed, OUTPUT);
    pinMode(GreenLed, OUTPUT);
}
 
void loop()
{
    if (SoftSerial.available())              
    {
        while(SoftSerial.available())               
        {
            ClearLeds();
            buffer[count++] = SoftSerial.read();      
            if(count == 64)break;
            RfidCatcher(buffer);
        }
        Serial.write(buffer, count);    
        clearBufferArray();             
        count = 0;                      
    }
    if (Serial.available())             
    SoftSerial.write(Serial.read()); 
}

/*
 * // RFID HANDLER API //
    Hardware Requirements :
    Generic system for better adapation
*/

// Catch RFID Code
void RfidCatcher(char rfid){
            Alarm();
            if(analyseRFID(rfid) == true){
                 digitalWrite(GreenLed, HIGH);
            }
}

// Analyse collected data
bool analyseRFID(char rfidToAnalyse){
  if(rfidToAnalyse == rfidToAnalyse){
    return true;
  }
}

// Clear Buffer
void clearBufferArray(){
    for (int i=0; i<count; i++){
        buffer[i]=NULL;
    }                  
}

/*
 * 
 * // LOW LEVEL API (Hardware Support //
    Hardware Requirements :

    - Arduino Uno
    - Base Shield V2 (Groove)
    - Leds
    - Buzzer 
    - RFID Reader
    (- Distant server for save RFID users)
     
    D2 = RFID Reader
    D4 = Green Led
    D6 = Buzzer
    D8 = Red Led
*/

void GreenLightOn(){
  digitalWrite(GreenLed, HIGH);
}

void RedLightOn(){
  digitalWrite(RedLed, HIGH);
}

void ClearLeds(){
  digitalWrite(GreenLed, LOW);
  digitalWrite(RedLed, LOW);
}

void Alarm(){

            digitalWrite(6, HIGH);
            delay(5);
            digitalWrite(6, LOW);
}