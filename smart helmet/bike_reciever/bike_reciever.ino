#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

RH_ASK rf_driver;

int state = 1;
int infLoop1 = 1;
const int pin = 9;
long gpslat, gpslon;

TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(2, 3);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();


void setup()
{
  sgsm.begin(9600);
  sgps.begin(9600);
  pinMode(8,OUTPUT);
  rf_driver.init();
  if(!accel.begin())
   {
      Serial.println("No valid sensor found");
      while(1);
   }
    Serial.begin(9600);
}

void loop()
{
  inpRec();
}
void inpRec()
{
  // Set buffer to size of expected message
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  sensors_event_t event;
  accel.getEvent(&event);
  Serial.println(event.acceleration.z);
  if((int)event.acceleration.z < 0){
    digitalWrite(8,LOW);
    getLoc();
    state = 0;
    infLoop1 = 0;
  }

  if (rf_driver.recv(buf, &buflen))
  {
    // Message received with valid che-cksum
    String buf1 = String((char *)buf);
    Serial.print("Message Received: ");
    Serial.println(buf1);
    if (buf1 == "ON")
    {
    Serial.println("motor:");
      digitalWrite(8,HIGH);
    }
    else if (buf1 == "OF") 
    {
     Serial.println("motor:off"); 
      digitalWrite(8,LOW);
    }
  }
  else{
    Serial.println("NO mSG");
  }
  delay(500);
}

void getLoc()
{

  while (infLoop1)
  {
    while (sgps.available() > 0 && state)
    {
      if (gps.encode(sgps.read()))
      {
        gps.get_position(&gpslat, &gpslon);
        Serial.println(gpslat);
        Serial.println(gpslon);
        state = 0;
        infLoop1 = 0;
        simActivate();
      }
    }
  }
}

void simActivate()
{
  Serial.print(gpslat);
  Serial.println(gpslon);
  Serial.print(gpslat / 1000000);
  Serial.print(".");
  Serial.print(gpslat % 1000000);
  Serial.print(",");
  Serial.print(gpslon / 1000000);
  Serial.print(".");
  Serial.println(gpslon % 1000000);

  sgsm.println("AT+CMGF=1"); // Sets the Sim Module in send SMS mode
                             //
  delay(1000);               // Delay of 1 second

  sgsm.println("AT+CMGS=\"+919840194432\""); // Replace x with mobile number

  delay(1000); // Delay of 1 second
  String text = "https://maps.google.com/?q=13.141994,80.114865";
  sgsm.print("Vimala is in danger. Kindly help her by touching this link. \n https://maps.google.com/?q="); // Type in the SMS text you want to send
  sgsm.print(gpslat / 1000000);
  sgsm.print(".");
  sgsm.print(gpslat % 1000000);
  sgsm.print(",");
  sgsm.print(gpslon / 1000000);
  sgsm.print(".");
  sgsm.println(gpslon % 1000000);
  delay(100); // Delay of 0.1 second

  sgsm.println((char)26); // ASCII code of CTRL+Z (to exit out)

  delay(1000); // Delay of 1 second
  Serial.println("end");
}
