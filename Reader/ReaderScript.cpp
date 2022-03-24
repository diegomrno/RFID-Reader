/*
    Buzzer on Socket D6
    RFID Reader on Socket D2
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
            buffer[count++] = SoftSerial.read();      
            if(count == 64)break;
            checkRfidCode(buffer);
            }
        Serial.write(buffer, count);    
        clearBufferArray();             
        count = 0;                      
    }
    if (Serial.available())             
    SoftSerial.write(Serial.read()); 
}

void checkRfidCode(char rfid){
  if(rfid == rfid){
      GreenLightOn(LedTime);
      Alarm(1);
  }
  else {
      RedLightOn(LedTime);
  }
}

void GreenLightOn(int time){
  digitalWrite(GreenLed, HIGH);
  delay(time);
  digitalWrite(GreenLed, LOW);
}

void RedLightOn(int time){
  digitalWrite(RedLed, HIGH);
  delay(time);
  digitalWrite(RedLed, LOW);
  Alarm(3);
}

void Alarm(int reccurence){
  for(int i = 0; i >= reccurence; i++){
    digitalWrite(6, HIGH);
    delay(15);
    digitalWrite(6, LOW);
  }
}

void clearBufferArray()                 
{
    for (int i=0; i<count; i++)
    {
        buffer[i]=NULL;
    }                  
}