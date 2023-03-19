#include <SoftwareSerial.h>

SoftwareSerial EEBlue(11, 12); // RX | TX
int IR1 = 8;                   // Right sensor
int IR2 = 9;                   // left Sensor

#define enA 10
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enB 5

int M1_Speed = 80;            // speed of motor 1
int M2_Speed = 80;            // speed of motor 2
int LeftRotationSpeed = 250;  // Left Rotation Speed
int RightRotationSpeed = 250; // Right Rotation Speed

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
}

void loop()

{

    // Feed any data from bluetooth to Terminal.

    int LEFT_SENSOR = digitalRead(A0);
    int RIGHT_SENSOR = digitalRead(A1);

    if (EEBlue.available())
    {
        String inpCmd = EEBlue.readString();
        Serial.println(inpCmd);
        if (inpCmd == 'FORWARD')
        {
            forward();
        }
        else if (inpCmd == 'RIGHT')
        {
            right();
        }
        else if (inpCmd == 'LEFT')
        {
            left();
        }
        else if (inpCmd == 'BACK')
        {
            backward();
        }
        else if (inpCmd == 'STOP')
        {
            backward();
        }
    }
    else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0)
    {
        forward(); // FORWARD
    }

    else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1)
    {
        right(); // Move Right
    }

    else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0)
    {
        left(); // Move Left
    }

    else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1)
    {
        Stop(); // STOP
    }
}
void forward()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, M1_Speed);
    analogWrite(enB, M2_Speed);
}

void backward()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, M1_Speed);
    analogWrite(enB, M2_Speed);
}

void right()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, LeftRotationSpeed);
    analogWrite(enB, RightRotationSpeed);
}

void left()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, LeftRotationSpeed);
    analogWrite(enB, RightRotationSpeed);
}

void Stop()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
