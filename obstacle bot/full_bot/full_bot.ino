#include <SoftwareSerial.h>

SoftwareSerial EEBlue(11, 12); // RX | TX
                               // left Sensor

#define enA 10
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enB 5

unsigned long last_time = 0;
int M1_Speed = 150;           // speed of motor 1
int M2_Speed = 150;           // speed of motor 2
int LeftRotationSpeed = 100;  // Left Rotation Speed
int RightRotationSpeed = 100; // Right Rotation Speed
int LEFT_SENSOR;
int RIGHT_SENSOR;
String inpCmd;
int state = 0;
int statedecide = 1;
char character;

void setup()

{

    Serial.begin(9600);
    Serial.println("begin");

    EEBlue.begin(9600); // Default Baud for comm, it may be different for your Module. Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    pinMode(A0, INPUT); // initialize Left sensor as an input
    pinMode(A1, INPUT);
    delay(10);
}

void loop()

{

    // Feed any data from bluetooth to Terminal.

    inpCmd = "";
    unsigned long now_time = millis();

    if (state == 0)
    {
        irCheck();
    }
    else
    {
        bluetoohControl();
    }
    if (statedecide)
    {
      Serial.print("text:");
        if (EEBlue.available())
        {
          
            state = 1;

            Serial.print("State:");
            Serial.println(state);
            
            statedecide = 0;
        }
        else
        {
            state = 0;
        }
    }

}

void bluetoohControl()
{
    while (EEBlue.available())
    {
        character = EEBlue.read();
        Serial.println(character);
        if (character == ' ')
        {
            break;
        }
        inpCmd.concat(character);
    }
        Serial.println(inpCmd);
    if (inpCmd == "FRONT")
    {
        forward();
    }
    else if (inpCmd == "RIGHT")
    {
        right();
    }
    else if (inpCmd == "LEFT")
    {
        left();
    }
    else if (inpCmd == "BACK")
    {
        backward();
    }
    else if (inpCmd == "STOP")
    {
        Stop();
    }
    delay(100);
}
void irCheck()
{
    LEFT_SENSOR = digitalRead(A0);
    RIGHT_SENSOR = digitalRead(A1);
    if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0)
    {
        forward(); // FORWARD
    }

    else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1)
    {
        left(); // Move Right
    }

    else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0)
    {

        right();
    }

    else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1)
    {
        Stop(); // STOP
    }
}
void forward()
{
    Serial.println("inside front");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, M1_Speed);
    analogWrite(enB, M2_Speed);
}

void backward()
{
    Serial.println("inside back");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, M1_Speed);
    analogWrite(enB, M2_Speed);
}

void right()
{
    Serial.println("inside right");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, LeftRotationSpeed);
    analogWrite(enB, RightRotationSpeed);
}

void left()
{
    Serial.println("inside left");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(enA, LeftRotationSpeed);
    analogWrite(enB, RightRotationSpeed);
}

void Stop()
{
    Serial.println("inside stop");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
}
