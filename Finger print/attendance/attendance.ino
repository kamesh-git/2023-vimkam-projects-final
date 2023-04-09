#include <Adafruit_Fingerprint.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
int servoPin = 13; 
// Create a servo object 
Servo myservo;

SoftwareSerial mySerial(0, 2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const char *ssid = "Vimkam";       // replace with your own SSID
const char *password = "12345678"; // replace with your own password
const char *host = "api.pushingbox.com";

int emergencyPin = 15;

String member = "";
int flag = 0;
void setup()
{
    pinMode(12,INPUT);
    delay(2000);


    Serial.begin(115200);
    pinMode(emergencyPin, INPUT);
    delay(10);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to WiFi...       ");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    myservo.attach(servoPin,600,2300);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(1500);

    while (!Serial)
        ;
    delay(100);
    Serial.println("\n\n Waiting for Fingerprint Sensor");
    delay(1500);
    finger.begin(57600);

    if (finger.verifyPassword())
    {
        Serial.println("Found Successfully");
        delay(1500);
    }
    else
    {
        Serial.println("Fingerprint sensor not found!!!");
        while (1)
        {
            delay(1);
        }
    }
    myservo.write(0); 
}

void loop()
{
    int fingerprintID = getFingerprintID();
    delay(50);
    if (fingerprintID == 1)
    {
        Serial.println("Welcome MANIVEL M");
        connecthost("MANIVEL%20M");
        flag = 0;
        handleGate();
    }
    else if (fingerprintID == 2)
    {
        Serial.println("Welcome SATHISH NARAYANAN S");
        connecthost("SATHISH%20NARAYANAN%20S ");
        flag = 0;
        handleGate();
    }
    else if (fingerprintID == 3)
    {
        Serial.println("Welcome SAKTHIPRIYAN B");
        connecthost("SAKTHIPRIYAN%20B");
        flag = 0;
        handleGate();
    }
    else if (fingerprintID == 4)
    {
        Serial.println("Welcome SANJAI R");
        connecthost("SANJAI%20R");
        flag = 0;
        handleGate();
    }
    else if (fingerprintID == 5)
    {
        Serial.println("Welcome MOSES EBINIZER C");
        connecthost("MOSES%20EBINIZER%20C");
        flag = 0;
        handleGate();
    }
    else
    {
        Serial.println("Waiting for valid finger!!!");
    }


    int emergency = digitalRead(emergencyPin);
    Serial.println(emergency);
    if(emergency == 1){
        myservo.write(90);
    }
    else{
         myservo.write(0);
    }


    
}

void handleGate(){
  Serial.print("waiting for man to pass:");
  myservo.write(90);
  while(digitalRead(12)){
    Serial.print(".");
  }
  myservo.write(0);
  Serial.println("man passed");
}

int getFingerprintID()
{
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)
        return -1;

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)
        return -1;

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)
        return -1;

    return finger.fingerID;
}

void connecthost(String data)
{
    if (flag == 0)
    {
        member = data;
        flag = 1;
        Serial.print("connecting to ");
        Serial.println(host);
        WiFiClient client;
        const int httpPort = 80;
        if (!client.connect(host, httpPort))
        {
            Serial.println("connection failed");
            return;
        }

        // We now create a URL for the request
        String url = "/pushingbox?";
        url += "devid=";
        url += "vC0427345170F134";
        url += "&Name=" + String(member);

        Serial.print("Requesting URL: ");
        Serial.println(url);
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
        while (client.available() == 0)
        {
            if (millis() - timeout > 5000)
            {
                Serial.println(">>> Client Timeout !");
                client.stop();
                return;
            }
        }
        while (client.available())
        {
            String line = client.readStringUntil('\r');
            Serial.print(line);
            Serial.print("Data Sent!");
        }

        Serial.println();
        Serial.println("closing connection");
    }
}
