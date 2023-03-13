/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */
 
#include <SoftwareSerial.h>

// The serial connection to the GPS module
SoftwareSerial sgps(11,12);
SoftwareSerial sgsm(2,3);

void setup(){
  Serial.begin(9600);
  sgsm.begin(9600);
//  sgps.begin(9600);
  
  
}

void loop(){
//  while (sgps.available() > 0){
//    // get the byte data from the GPS
//    byte gpsData = sgps.read();
//    Serial.write(gpsData);
//  }

if (sgsm.available()>0){

   Serial.write(sgsm.read());                  // If SIM module sends messages, print it to Serial monitor

}
oneTime();

}
void oneTime(){
  Serial.println("loop");
sgsm.listen();
delay(1000);
sgsm.print("AT+CMGF=1\r");
}
