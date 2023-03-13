#include <SoftwareSerial.h>
#include <TinyGPS.h>

int state = 1;
const int pin = 9;
long gpslat, gpslon;

TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(2, 3);

void setup()
{
    sgsm.begin(9600);
  sgps.begin(9600);
//  Serial.begin(9600);
}

void loop()
{
  while (sgps.available()>0 && state)
  {
    if (gps.encode(sgps.read()))
    {
      gps.get_position(&gpslat, &gpslon);
      Serial.println(gpslat);
      Serial.println(gpslon);
      state = 0;
      simActivate();
    }
  }
}

void simActivate(){
  Serial.print(gpslat);
  Serial.println(gpslon);
  Serial.print(gpslat/1000000); 
  Serial.print("."); 
  Serial.print(gpslat%1000000); 
  Serial.print(","); 
  Serial.print(gpslon/1000000); 
  Serial.print("."); 
  Serial.println(gpslon%1000000);

  sgsm.println("AT+CMGF=1");                    // Sets the Sim Module in send SMS mode
//
  delay(1000);                                 // Delay of 1 second

  sgsm.println("AT+CMGS=\"+919840194432\"");  // Replace x with mobile number

  delay(1000);                                 // Delay of 1 second
  String text = "https://maps.google.com/?q=13.141994,80.114865";
  sgsm.print("Vimala is in danger. Kindly help her by touching this link. \n https://maps.google.com/?q=");     // Type in the SMS text you want to send
  sgsm.print(gpslat/1000000); 
  sgsm.print("."); 
  sgsm.print(gpslat%1000000); 
  sgsm.print(","); 
  sgsm.print(gpslon/1000000); 
  sgsm.print("."); 
  sgsm.println(gpslon%1000000); 
  delay(100);                                  // Delay of 0.1 second

  sgsm.println((char)26);                       // ASCII code of CTRL+Z (to exit out)

  delay(1000);                                 // Delay of 1 second
  Serial.println("end");
}
