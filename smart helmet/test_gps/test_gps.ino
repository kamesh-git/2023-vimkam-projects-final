/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */
 
#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;  

// The serial connection to the GPS module
SoftwareSerial sgps(4,5);
SoftwareSerial sgsm(2,3);
long gpslat, gpslon;
int state =1;

void setup(){
  Serial.begin(9600);
//  sgsm.begin(9600);
  sgps.begin(9600);
  
  
}

void loop(){
  while (sgps.available() > 0 && state){
//    if (gps.encode(sgps.read()))
//      {
//        gps.get_position(&gpslat, &gpslon);
//        Serial.println(gpslat);
//        Serial.println(gpslon);
//
//      }
byte dat = sgps.read();
Serial.write(dat);
    // get the byte data from the GPS
  }
  


}
void oneTime(){
  Serial.println("loop");
sgsm.listen();
delay(1000);
sgsm.print("AT+CMGF=1\r");
}
