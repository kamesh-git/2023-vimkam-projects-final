#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>  // Includes the PulseSensorPlayground Library.
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <SPI.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <Adafruit_BMP280.h>

#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp; // I2C

SoftwareSerial espSerial(6,7);

#define ONE_WIRE_BUS 8
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

// Variables
const int PulseWire = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 1;    // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;     // Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
int speakerPin = 13;

PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

int myBPM;
float tempVal;
float myPres;
void setup()
{

    Serial.begin(9600); // For Serial Monitor
    lcd.begin(16, 2);
    sensors.begin();
    espSerial.begin(115200);
    pinMode(speakerPin,OUTPUT);

    status = bmp.begin(BMP280_ADDRESS);
    if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


    // Configure the PulseSensor object, by assigning our variables to it.
    pulseSensor.analogInput(PulseWire);
    pulseSensor.blinkOnPulse(LED13); // auto-magically blink Arduino's LED with heartbeat.
    pulseSensor.setThreshold(Threshold);

    // Double-check the "pulseSensor" object was created and "began" seeing a signal.
    if (pulseSensor.begin())
    {

        +Serial.println("We created a pulseSensor Object !"); // This prints one time at Arduino power-up, or on Arduino reset.
    }
}

void loop()
{
    getTemp();
    getHeartRate();
    myPres = bmp.readPressure();
    Serial.print("pressure:");
    Serial.println(myPres);
   lcdDisplay();
   espSerial.println((String) tempVal + " " + myBPM + " " + myPres);

//    buzzer
}

void getTemp(){
    sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  tempVal = sensors.getTempCByIndex(0);
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(1000);
}

void getHeartRate()
{

myBPM = pulseSensor.getBeatsPerMinute();
    // Calls function on our pulseSensor object that returns BPM as an "int".
    // "myBPM" hold this BPM value now.
;    if (pulseSensor.sawStartOfBeat())
    {                                                // Constantly test to see if "a beat happened".
        Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
        Serial.print("BPM: ");                       // Print phrase "BPM: "
        Serial.println(myBPM);   
//        if(myBPM > 240){
//          digitalWrite(speakerPin,HIGH);
//        }
//        else{
//          digitalWrite(speakerPin,LOW);
//        }
    }
    delay(20); // considered best practice in a simple sketch.
}

void lcdDisplay()
{
    lcd.setCursor(0, 0);
    lcd.print("                   ");
    lcd.setCursor(0, 0);
    lcd.print("Temp: "); // If test is "true", print a message "a heartbeat happened".
    lcd.print(tempVal);
    lcd.setCursor(0, 1);
    lcd.print("                   ");
    lcd.setCursor(0, 1);
    lcd.print("Heart: "); // Print phrase "BPM: "
    lcd.print(myBPM);
}
