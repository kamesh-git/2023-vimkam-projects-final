#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

void setup()
{
  
  Serial.begin(9600);
  
 
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT");
  updateSerial();

  mySerial.println("AT+CMGF=0"); 
  updateSerial();
  mySerial.println("AT+CMGS=\"+918610769361\""); // enter your phone number here (prefix country code)
  updateSerial();
  mySerial.print("Hello kamesh"); // enter your message here
  updateSerial();
  mySerial.write(26);
  Serial.println("end");
}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
