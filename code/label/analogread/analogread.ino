

float V1,V2,V3,V4,V5,V6;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pins with the adc func:
  int AV1 = analogRead(8);
  int AV2 = analogRead(11);
  int AV3 = analogRead(13);
  int AV4 = analogRead(15);
  int AV5 = analogRead(24);
  int AV6 = analogRead(34);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  V1 = AV1 * (5.0 / 1023.0);
  V2 = AV2 * (5.0 / 1023.0);
  V3 = AV3 * (5.0 / 1023.0);
  V4 = AV4 * (5.0 / 1023.0);
  V5 = AV5 * (5.0 / 1023.0);
  V6 = AV6 * (5.0 / 1023.0);
}
