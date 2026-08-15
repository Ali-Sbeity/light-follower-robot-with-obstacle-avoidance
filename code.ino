#include <Servo.h>

Servo radarServo;

const int trigPin = 5;
const int echoPin = 4;

const int servoPin = 3;

const int in1 = 10;
const int in2 = 9;
const int in3 = 8;
const int in4 = 7;

const int enA =11;
const int enB = 6;

const int buttonPin = 2;
const int statusLed = 13;

const int ldrLeft = A0;
const int ldrCenter = A1;
const int ldrRight = A2;

bool robotOn = false;
int lastButtonState = HIGH;

const int lightThreshold = 400;
const int stopThreshold = 900;
const int tolerance = 50;

int obstacleDistance = 10;

int forwardSpeed = 80;
int turnSpeed = 60;

int leftLightValue = 0;
int centerLightValue = 0;
int rightLightValue = 0;

int leftDistanceValue;
int rightDistanceValue;


void setup()
{
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(statusLed, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  radarServo.attach(servoPin);

  radarServo.write(90);

  Serial.begin(9600);
}

void loop()
{
  readButton();
  if(robotOn)
  {
    digitalWrite(statusLed, HIGH);
    runRobot();
  }
  else
  {
    stopRobot();
    digitalWrite(statusLed, LOW);
  }
}



void readButton()
{
  int buttonState = digitalRead(buttonPin);
  
  if(buttonState == LOW && lastButtonState == HIGH)
  {
    robotOn = !robotOn;
  }
  lastButtonState = buttonState;
}


void followLight()
{
  leftLightValue = analogRead(ldrLeft);
  centerLightValue = analogRead(ldrCenter);
  rightLightValue = analogRead(ldrRight);

  Serial.print("left light value");
  Serial.println(leftLightValue);

  Serial.print("center light value");
  Serial.println(centerLightValue);

  Serial.print("right light value");
  Serial.println(rightLightValue);

  if(leftLightValue > stopThreshold || centerLightValue > stopThreshold || rightLightValue > stopThreshold)
  {
    stopRobot();
    return;
  }

  if(leftLightValue < lightThreshold && centerLightValue < lightThreshold && rightLightValue < lightThreshold)
  {
    stopRobot();
    return;
  }

  if(leftLightValue > centerLightValue + tolerance && leftLightValue > rightLightValue + tolerance)
  {
    turnLeft();
  }

  else if(rightLightValue > centerLightValue + tolerance && rightLightValue > leftLightValue + tolerance)
  {
    turnRight();
  }

  else
  {
    moveForward();
  }
}


void runRobot()
{
  int distance = getDistance();

  Serial.print("front:");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance > obstacleDistance)
  {
    followLight();
  }
  else
  {
    avoidObstacle();
  }
}


void avoidObstacle()
{
  stopRobot();
  leftDistanceValue = lookLeft();
  rightDistanceValue = lookRight();
  radarServo.write(90);
  delay(300);
  chooseDirection();
}


void chooseDirection()
{
  if(leftDistanceValue <= obstacleDistance && rightDistanceValue <= obstacleDistance)
  {
    Serial.println("blocked");
    stopRobot();
    delay(500);
    return;
  }

  if(leftDistanceValue > rightDistanceValue)
  {
    turnLeft();
  }

  else
  {
    turnRight();
  }
    delay(400);
    stopRobot();
    moveForward();
    delay(800);
    stopRobot();
}


int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}



void moveForward()
{
  analogWrite(enA, forwardSpeed);
  analogWrite(enB, forwardSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void turnLeft()
{
  analogWrite(enA, turnSpeed);
  analogWrite(enB, turnSpeed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void turnRight()
{
  analogWrite(enA, turnSpeed);
  analogWrite(enB, turnSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void stopRobot()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}



int lookLeft()
{
  radarServo.write(0);
  delay(500);
  int distance = getDistance();

  Serial.print("left:");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}


int lookRight()
{
  radarServo.write(180);
  delay(500);
  int distance = getDistance();

  Serial.print("right:");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}
