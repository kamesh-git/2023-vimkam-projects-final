
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;

char ssid[] = "Galaxy M11";
char pass[] = "arulsamsung";
#define BLYNK_TEMPLATE_ID "TMPLeg8dm7aq"
#define BLYNK_TEMPLATE_NAME "Patient health monitor"
#define BLYNK_AUTH_TOKEN "qNMwEZOdgECYgDylzkY9ceDa4bmUFvof"
int i = 1;
String one;
String two;

void setup()
{
  Serial.begin(115200);

  timer.setInterval(1000L, myTimer);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
}

void loop()
{
  String s = Serial.readString();
  Serial.println(s);
  int space = s.indexOf(" ");
  int l = s.length();
  one = s.substring(0, space);
  two = s.substring(space + 1, l);
  Blynk.run();
  timer.run();
  Serial.println(one.toInt()+two.toInt());
}

void myTimer()
{
  if (one && two)
  {
    Blynk.virtualWrite(V0, one.toInt());
    Blynk.virtualWrite(V1, two.toInt());
  }
}
