#include <Arduino.h>


#include "string.h"

char message[20];

int CheckSum;  


int received_data[9];    //datas measured by LiDAR
const int HEADER=0x59;  //frame header of data package

 #define RX2 17
#define TX2 16

 //#define RX1 33
 //#define TX1 25 //lidar rx

 #define RX1 21
 #define TX1 22


int dist;                     //actual distance measurements of LiDAR

int check;                    //save check value

int uart[9];                   //save data measured by LiDAR


int dist1;                     //actual distance measurements of LiDAR
                 //signal strength of LiDAR
int check1;                    //save check value
int i;
int uart1[9];                   //save data measured by LiDAR


void setup() {
 
  Serial.begin(115200);
  Serial1.begin(115200,SERIAL_8N1,RX1,TX1);
  Serial2.begin(115200,SERIAL_8N1,RX2,TX2);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(4,OUTPUT);
 
}

void lidars(){

  if(Serial1.available()||Serial2.available()){
     
  
    if (Serial1.read() == HEADER)        //assess data package frame header 0x59
    {
      uart[0] = HEADER;
      if (Serial1.read() == HEADER)      //assess data package frame header 0x59
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)         //save data in array
        {
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))        //verify the received data as per protocol
        {
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          
          
        }
      }
    
  }
else{
   
  dist=0;
}
 if (Serial2.read() == HEADER)        //assess data package frame header 0x59
    {
      uart[0] = HEADER;
      if (Serial2.read() == HEADER)      //assess data package frame header 0x59
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)         //save data in array
        {
          uart[i] = Serial2.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))        //verify the received data as per protocol
        {
          dist1 = uart[2] + uart[3] * 256;     //calculate distance value
          
          
        }
      }
    
  }
else{
   
  dist1=0;
}
          
 
  
}
else{
       dist=0;
       dist1=0;  
 }
/*
Serial.print("[04:00:01;");
Serial.print(dist);              
Serial.print(":02;");
Serial.print(dist1);     
Serial.print(']');
*/

String first="[04:00:01;";
String third=":02;";
String _final="]";

Serial.println(first+dist+third+dist1+_final);

delay(10);

}


void loop() { 
    
  String readString;
String Q;


 while (Serial.available()){
  delay(1);
  if(Serial.available()>0){
  char c = Serial.read();
   if (isControl(c)){
  break;
  }
  readString += c;    
  }
 }

Q = readString;
if (Q=="[04:01:01:01]"){
  digitalWrite(12,HIGH);
 }

if (Q=="[04:01:01:00]"){
 digitalWrite(12,LOW);
}
if (Q=="[04:01:02:01]"){
  digitalWrite(13,HIGH);
 }

if (Q=="[04:01:02:00]"){
 digitalWrite(13,LOW);
}

if (Q=="[04:01:03:01]"){
  digitalWrite(4,HIGH);
 }

if (Q=="[04:01:03:00]"){
 digitalWrite(4,LOW);
}
       lidars();
     
    
      
}