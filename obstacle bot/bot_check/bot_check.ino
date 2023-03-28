#define enA 10
#define in1 8
#define in2 9
#define in3 7
#define in4 6
#define enB 5

unsigned long last_time = 0;
int M1_Speed = 250;           // speed of motor 1
int M2_Speed = 250;           // speed of motor 2
int LeftRotationSpeed = 200;  // Left Rotation Speed
int RightRotationSpeed = 200; // Right Rotation Speed
int LEFT_SENSOR;
int RIGHT_SENSOR;

void setup()

{

    Serial.begin(9600);
    Serial.println("begin");

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    pinMode(A0, INPUT); // initialize Left sensor as an input
    pinMode(A1, INPUT);
}

void loop(){
    left();
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
    Serial.println("inside left");
    digitalWrite(in1, HIGH);
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
    digitalWrite(in2, HIGH);
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
//    digitalWrite(in3, LOW);
//    digitalWrite(in4, LOW);

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
