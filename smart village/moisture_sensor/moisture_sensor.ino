int DRY = 2;       // Dry Indicator at Digital pin D4
int sense_Pin = 0; // sensor input at Analog pin A0
int inputPin = 13; // choose input pin (for Infrared sensor) - D7
int val = 0;       // variable for reading the infra red pin status

int value = 0;
void setup()
{
    Serial.begin(9600);
    pinMode(WET, OUTPUT);
    pinMode(DRY, OUTPUT);
    delay(2000);
}
void loop()
{

    // moisture sensor part
    Serial.print("MOISTURE LEVEL : ");
    value = analogRead(sense_Pin);
    value = value / 10;
    Serial.println(value);

    if (value < 50)
    {
        digitalWrite(WET, HIGH);
    }
    else
    {
        digitalWrite(DRY, HIGH);
    }

    delay(1000);

    digitalWrite(WET, LOW);

    digitalWrite(DRY, LOW);

    //    infrared sensor part

        
    Serial.print("infrared sensor");
    Serial.println(val);
}