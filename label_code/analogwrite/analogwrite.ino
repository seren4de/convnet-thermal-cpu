#include<math.h>

float f ;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
    for(int i=0;i<100;i++)
    {
       f = (3276*sin(i)+32767);
        // read the input on analog pins with the adc func:
     analogWrite(8,f);
     analogWrite(11,2*f);
     analogWrite(13,3*f);
     analogWrite(15,4*f);
     analogWrite(24,9*f);
     analogWrite(34,20*f);
    }
}
