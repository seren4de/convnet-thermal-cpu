#include <SoftwareSerial.h>


String words1[117];
String words2[117];
String words3[117];

SoftwareSerial serial1(33, 11); // RX, TX
SoftwareSerial serial2(37, 35); // RX, TX
SoftwareSerial serial3(12, 14); // RX, TX


void setup() {
  
  serial1.begin(1200);
  serial2.begin(2400);
  serial3.begin(4800);
 
  }


void loop() {
  for (int i = 0; i<117;i++){
   
    words1[i]= serial1.read();
    words2[i]= serial2.read();
    words3[i]= serial3.read();}
   
}
