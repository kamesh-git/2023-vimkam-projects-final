#include <SoftwareSerial.h>

SoftwareSerial EEBlue(9, 8); // RX | TX



#define enA 6
#define in1 7
#define in2 5
#define in3 4
#define in4 2
#define enB 3
#define echoPin A0 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin A1 // attach pin D3 Arduino to pin Trig of HC-SR04

int M1_Speed = 150;           // speed of motor 1
int M2_Speed = 150;           // speed of motor 2
int LeftRotationSpeed = 100;  // Left Rotation Speed
int RightRotationSpeed = 100; // Right Rotation Speed

long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

String inpCmd;
char character;

void setup()
{

    Serial.begin(9600);
    Serial.println("begin");

    // power pins

    EEBlue.begin(9600); // Default Baud for comm, it may be different for your Module. Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT

    delay(10);
}

void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

    inpCmd = "";

    while (EEBlue.available())
    {
        character = EEBlue.read();
        Serial.print("recieved:");
        Serial.println(character);
        if (character == ' ' || character == '\n')
        {
            break;
        }
        inpCmd.concat(character);
    }
    inpCmd.replace("*", "");
    inpCmd.replace("#", "");
    inpCmd.toUpperCase();
    Serial.println(inpCmd);
    Serial.print("distance");
    Serial.println(distance);
    if(distance < 10){
        Stop();
    }
    else if (inpCmd == "FRONT" || inpCmd == "F")
    {
        forward();
    }
    else if (inpCmd == "RIGHT" || inpCmd == "R")
    {
        right();
    }
    else if (inpCmd == "LEFT" || inpCmd == "L")
    {
        left();
    }
    else if (inpCmd == "BACK" || inpCmd == "B")
    {
        backward();
    }
    else if (inpCmd == "STOP" || inpCmd == "S")
    {
        Stop();
    }
    delay(100);
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
