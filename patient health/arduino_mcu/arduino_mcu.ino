#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 6);
int i = 1;
void setup(){
Serial.begin(9600);
espSerial.begin(115200);
delay(2000);
}
void loop(){
  Serial.println(i);
  espSerial.println((String) 12 + " " + 13);
//  espSerial.println(i++);
  delay(1000);
}
