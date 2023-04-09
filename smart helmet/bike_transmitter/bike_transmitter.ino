#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h>    // Include dependant SPI Library

RH_ASK rf_driver;
const int flexPin = A1; // pin A0 to read flex analog input
const int MQ3 = A0;     // pin A1 to read MQ3 analog input
int flexValue;
float sensorValue;

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  // Initialize ASK Object
  rf_driver.init();
  Serial.println("MQ3 Heating Up!");
  delay(20000); // allow the MQ3 to warm up
}

void loop()
{
  flexValue = analogRead(flexPin);
  sensorValue = analogRead(MQ3); // read analog input pin 0

  Serial.print("flexValue:");
  Serial.println(flexValue);
  Serial.print("sensorValue:");
  Serial.println(sensorValue);
  if (flexValue < 700 && sensorValue < 550)
  {

    sendMsg("ON");
  }
  else
  {
    sendMsg("OF");
  }
}

void sendMsg(char *msg)
{
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
  {
    // Message Transmitted
    Serial.print("Message Transmitted: ");
    Serial.println(msg);
    delay(1000);
  }
}
