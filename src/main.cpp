#include <Arduino.h>

#include "string.h"

char message[20];
int distance;   //actual distance measurements of LiDAR
int strength;   //signal strength of LiDAR
int temperature;    //temperature of LiDAR
int CheckSum;  


int received_data[9];    //datas measured by LiDAR
const int HEADER=0x59;  //frame header of data package

 #define RX1 16
#define TX1 17

 //#define RX1 33
 //#define TX1 25 //lidar rx

 #define RX2 21
 #define TX2 22


int dist;                     //actual distance measurements of LiDAR

int check;                    //save check value

int uart[9];                   //save data measured by LiDAR


int dist1;                     //actual distance measurements of LiDAR
int strength1;                 //signal strength of LiDAR
int check1;                    //save check value
int i;
int uart1[9];                   //save data measured by LiDAR


void setup() {
 
  Serial.begin(115200);
  Serial1.begin(115200,SERIAL_8N1,RX1,TX1);
  Serial2.begin(115200,SERIAL_8N1,RX2,TX2);
  pinMode(4,OUTPUT);
 
}
void Read_Lidar(){

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

Serial.print("dist 1  = ");
          Serial.print(dist);              
         
          Serial.print(" ****  dist 2  = ");
          Serial.print(dist1);     
          Serial.print('\n');
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
if (Q=="1"){
  digitalWrite(4,HIGH);
 }

if (Q=="2"){
 digitalWrite(4,LOW);
}

if (Q=="3"){
  
 }

       Read_Lidar();
     
    
      
}
