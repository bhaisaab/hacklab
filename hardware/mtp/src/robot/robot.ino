/*****************************************************************************
 * robot.pde: Code for driving wireless robot
 * Author: Rohit Yadav <rohit.yadav.cse07@itbhu.ac.in>
 *****************************************************************************/

#include <Servo.h>
#include "language.h"

#define LeftMotorPinA       4
#define LeftMotorPinB       5
#define RightMotorPinA      6
#define RightMotorPinB      7

#define servoMotorPin       11
#define proximitySensorPin  0

Servo proximityServo;
volatile int servoPos = 90;

volatile int _wordSet;
volatile int _wordSetVerb;
volatile int _wordSetDirection;
volatile int _wordSetQuantity;

unsigned char autoMode = FALSE;
unsigned char cmdReceived = FALSE;

void resetWordSetState()
{
  _wordSet = 0;
  _wordSetVerb = STOP_CMD; //STOP
  _wordSetDirection = 0;
  _wordSetQuantity = 0;
}

void setup(void)
{
  pinMode(LeftMotorPinA,   OUTPUT);
  pinMode(LeftMotorPinB,   OUTPUT);
  pinMode(RightMotorPinA,  OUTPUT);
  pinMode(RightMotorPinB,  OUTPUT);
  pinMode(servoMotorPin,   OUTPUT);

  proximityServo.attach(servoMotorPin);
  proximityServo.write(servoPos);
  resetWordSetState();

  stop();
  Serial.begin(9600);
}

void loop(void)
{
  // Incoming signal as 3 packets
  if(Serial.available() > 0)
  {
    unsigned char incomingByte = Serial.read();
    if(incomingByte == START_CMD)
    {
      resetWordSetState();
      while(1) // Loop until you get the var
      if(Serial.available() > 0)
      {
        unsigned char incomingByte = Serial.read();
        if(incomingByte == END_CMD)
        {
          cmdReceived = TRUE;
          break;
        }
        switch(_wordSet)
        {
          case 0:
            _wordSetVerb = incomingByte;
            _wordSet++;
            break;
          case 1:
            _wordSetDirection = incomingByte;
            _wordSet++;
            break;
          case 2:
            if(incomingByte >= '0' && incomingByte <= '9')
              _wordSetQuantity = incomingByte - '0';
            else
              _wordSetQuantity = 10;
            _wordSet++;
            break;
          default:
            break;
        }
      }
      runCmd();
    }
  }

  // Check and auto navigate
  if( autoMode == TRUE)
    runAutonomously();
  else
    if(getProximity() <= 10)
      stop();
}

void runCmd()
{
  //Serial.println("runCmd");
  autoMode = FALSE;
  switch(_wordSetVerb)
  {
    // 2 word sentence
    case RUN_CMD:
    // 3 word sentence
    case MOVE_CMD:
      switch(_wordSetDirection)
      {
        case LEFT_CMD:
          left(); break;
        case RIGHT_CMD:
          right(); break;
        case FORWARD_CMD:
          forward(); break;
        case BACKWARD_CMD:
          backward(); break;
        default: //some other cmd
          break;
      }
      if(_wordSetVerb == MOVE_CMD)
      {
        delay(_wordSetQuantity * 1000);
        stop();
      }
      break;
    // 1 word sentence
    case ACTION_CMD:
      autoMode = TRUE;
      break;
    case LOOK_CMD:
      sendDistanceData();
      break;
    case HELLO_CMD:
      proximityServo.write(0);
      delay(300);
      proximityServo.write(90);
      delay(300);
      proximityServo.write(180);
      delay(300);
      proximityServo.write(90);
      break;
    case STOP_CMD:
    default:
      stop();
      break;
    }
}

void runAutonomously()
{
  //Serial.println("runAuto");
  int proximity = getProximity();

  if(proximity > 40)
    forward();

  if(proximity < 20)
    backward();

  if(proximity <= 40 && proximity >= 20)
  {
    stop();
    for(servoPos = 0; servoPos <= 180; servoPos+=15)
    {
      proximityServo.write(servoPos);
      if(getProximity() > 40)
        break;
    }
    if(servoPos < 90) // move left
      left();
    else if(servoPos > 160)
      backward();
    else // move right
      right();

    delay(700);
    servoPos = 90;
    proximityServo.write(servoPos);
    stop();
    delay(100);
  }
}

// Gets proximity in cm
int getProximity()
{
  float total = 0;
  int index = 0;
  int numReadings = 10;
  for (index = 0; index <= numReadings;index++) // take average of 10 readings
  {
    // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    float volts = analogRead(proximitySensorPin)*0.0048828125;
    // worked out from graph 65 = theretical distance / (1/Volts)S
    float distance = 65*pow(volts, -1.10);
    total += distance;
    delay(20);
  }
  return total/numReadings;
}

void sendDistanceData()
{
  //Serial.println("sendDistanceData");
  // left to right
  for(servoPos = 0; servoPos < 180; servoPos++)
  {
    proximityServo.write(servoPos);
    Serial.print("X");
    Serial.print(servoPos);
    Serial.print("V");
    Serial.println(getProximity());
  }
  //right to left
  for(servoPos = 180; servoPos > 0; servoPos--)
  {
    proximityServo.write(servoPos);
    Serial.print("X");
    Serial.print(servoPos);
    Serial.print("V");
    Serial.println(getProximity());
  }
  Serial.println(END_CMD);
  Serial.flush();
  servoPos = 90;
  proximityServo.write(servoPos);
}

void stop(void)
{
  //Serial.println("stop");
  digitalWrite(LeftMotorPinA,   HIGH);
  digitalWrite(LeftMotorPinB,   HIGH);
  digitalWrite(RightMotorPinA,  HIGH);
  digitalWrite(RightMotorPinB,  HIGH);
}

void forward(void)
{
  //Serial.println("forward");
  digitalWrite(LeftMotorPinA,   HIGH);
  digitalWrite(LeftMotorPinB,   LOW);
  digitalWrite(RightMotorPinA,  HIGH);
  digitalWrite(RightMotorPinB,  LOW);
}

void backward(void)
{
  //Serial.println("backward");
  digitalWrite(LeftMotorPinA,   LOW);
  digitalWrite(LeftMotorPinB,   HIGH);
  digitalWrite(RightMotorPinA,  LOW);
  digitalWrite(RightMotorPinB,  HIGH);
}

void right(void)
{
  //Serial.println("right");
  digitalWrite(LeftMotorPinA,   HIGH);
  digitalWrite(LeftMotorPinB,   HIGH);
  digitalWrite(RightMotorPinA,  HIGH);
  digitalWrite(RightMotorPinB,  LOW);
}

void left(void)
{
  //Serial.println("left");
  digitalWrite(LeftMotorPinA,   HIGH);
  digitalWrite(LeftMotorPinB,   LOW);
  digitalWrite(RightMotorPinA,  HIGH);
  digitalWrite(RightMotorPinB,  HIGH);
}
