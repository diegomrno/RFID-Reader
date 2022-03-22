/*
    Buzzer on Socket D6
    RFID Reader on Socket D2
*/
 
#include <SoftwareSerial.h>
 
SoftwareSerial SoftSerial(2, 3);
unsigned char buffer[64];      
int count = 0;                  
 
void setup()
{
    SoftSerial.begin(9600);   
    Serial.begin(9600);    
    pinMode(6, OUTPUT);
}
 
void loop()
{
    if (SoftSerial.available())              
    {
        while(SoftSerial.available())               
        {
            buffer[count++] = SoftSerial.read();      
            if(count == 64)break;
            
            digitalWrite(6, HIGH);
            delay(1000);
            digitalWrite(6, LOW);
        }
        Serial.write(buffer, count);    
        clearBufferArray();             
        count = 0;                      
    }
    if (Serial.available())             
    SoftSerial.write(Serial.read()); 
}
void clearBufferArray()                 
{
    for (int i=0; i<count; i++)
    {
        buffer[i]=NULL;
    }                  
}