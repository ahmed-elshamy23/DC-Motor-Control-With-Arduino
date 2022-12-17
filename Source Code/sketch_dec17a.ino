#define LED_PIN 13
#define TRIG_PIN 4
#define ECHO_PIN 3

#define IN1 13
#define IN2 12
#define IN3 11
#define IN4 10
#define ENA 9
#define ENB 6

#define CLOCKWISE 0
#define ANTI_CLOCKWISE 1

#define FULL_SPEED 240

void DC_controlSpeedAndDirection(unsigned char motorNumber, unsigned char speed, unsigned char direction)
{
  switch(motorNumber)
  {
  case 1:
    switch(direction)
    {
    case CLOCKWISE:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, speed);
      break;
    case ANTI_CLOCKWISE:
      digitalWrite(IN2, HIGH);
      digitalWrite(IN1, LOW);
      analogWrite(ENA, speed);
      break;
    }
    break;
  case 2:
    switch(direction)
    {
    case CLOCKWISE:
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, speed);
      break;
    case ANTI_CLOCKWISE:
      digitalWrite(IN4, HIGH);
      digitalWrite(IN3, LOW);
      analogWrite(ENB, speed);
      break;
    }
    break;
  }
}

float echoHighTime;
unsigned char distance, motorSpeed = 100;

void setup()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}
void loop()
{
    digitalWrite(TRIG_PIN, HIGH);
    delay(1);
    digitalWrite(TRIG_PIN, LOW);
    echoHighTime = pulseIn(ECHO_PIN, HIGH);
    distance = echoHighTime * 0.034f / 2.0f;
    if (distance <= 40)
    {
        DC_controlSpeedAndDirection(1, motorSpeed, CLOCKWISE);
        DC_controlSpeedAndDirection(2, motorSpeed, CLOCKWISE);
    }
    else if(distance <= 10)
    {
        motorSpeed = 0;
        DC_controlSpeedAndDirection(1, motorSpeed, CLOCKWISE);
        DC_controlSpeedAndDirection(2, motorSpeed, CLOCKWISE);
    }
    else
    {
        DC_controlSpeedAndDirection(1, FULL_SPEED, CLOCKWISE);
        DC_controlSpeedAndDirection(2, FULL_SPEED, CLOCKWISE);
    }
    delay(100);
}
