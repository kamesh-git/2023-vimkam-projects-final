#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP);

BlynkTimer timer;

char ssid[] = "Vimkam";
char pass[] = "12345678";
#define BLYNK_TEMPLATE_ID "TMPL6uEHZX7p"
#define BLYNK_TEMPLATE_NAME "Samrt Village"
#define BLYNK_AUTH_TOKEN "adHC-P1loApgfc1T5THd7ijgkhNjZn4V"

int h = 18;
int m = 0;
int d_diff;
int m_diff;
int moistValue;
int irValue;
int sense_Pin = 0; // A0 pin
int irPin = 15;    // D8

void setup()
{
  Serial.begin(9600);

  timer.setInterval(1000L, myTimer);

  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(5, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);

  timeClient.begin();
  timeClient.setTimeOffset(19800);
}

void loop()
{
  Blynk.run();
  timeClient.update();
  moistValue = analogRead(sense_Pin);
  irValue = digitalRead(irPin); // read input value

  if (h - timeClient.getHours() <= 0 && m - timeClient.getMinutes() <= 0)
  {
    Blynk.virtualWrite(V2, 1);
    digitalWrite(5, 0);
  }
  else
  {
    Blynk.virtualWrite(V2, 0);
    digitalWrite(5, 1);
  }
  if (moistValue > 600)
  {
    Blynk.virtualWrite(V6, 0);
    digitalWrite(12, 0);
  }
  else
  {
    Blynk.virtualWrite(V6, 1);
    digitalWrite(12, 1);
  }
  if (irValue)
  {
    Blynk.virtualWrite(V7, 0);
    digitalWrite(13, 1);
  }
  else
  {
    Blynk.virtualWrite(V7, 1);
    digitalWrite(13, 0);
  }
  delay(1000);
}

void myTimer()
{
}

BLYNK_WRITE(V0) // Executes when the value of virtual pin 0 changes
{
  h = param.asInt();
  Serial.println("hours");
}
BLYNK_WRITE(V1) // Executes when the value of virtual pin 1 changes
{
  m = param.asInt();
  Serial.println("mins");
}

BLYNK_WRITE(V2)
{ // led on
  int state = param.asInt();
  digitalWrite(5, !state); // D1
  Serial.println("LED");
}
BLYNK_WRITE(V6)
{ // motor on
  int state = param.asInt();
  digitalWrite(12, state); // D6
}
BLYNK_WRITE(V7)
{ // fan on
  int state = param.asInt();
  Serial.println(state);
  digitalWrite(13, state); // D7
}
