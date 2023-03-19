#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>  // Includes the PulseSensorPlayground Library.
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

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
void setup()
{

    Serial.begin(9600); // For Serial Monitor
    lcd.begin(16, 2);
    sensors.begin();
    espSerial.begin(115200);
    pinMode(speakerPin,OUTPUT);


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
   lcdDisplay();
   espSerial.println((String) tempVal + " " + myBPM);
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
