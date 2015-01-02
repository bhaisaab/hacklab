/*****************************************************************************
 * basestation.pde: Code for the base station
 * Author: Rohit Yadav <rohit.yadav.cse07@itbhu.ac.in>
 *****************************************************************************/

#include "protocol.h"
#include "language.h"

/* Speech Recognition Status */
#define errorStatusPin   8
#define readyStatusPin   3
#define triggerButtonPin 2

#define wordSetZeroPin   7
#define wordSetOnePin    6
#define wordSetTwoPin    5
#define wordSetThreePin  4

uint8_t _receivePin;
uint8_t _transmitPin;
long _baudRate;
int _bitPeriod;

int _sRDetect;

volatile int _wordSet;
volatile int _wordSetVerb;
volatile int _wordSetDirection;
volatile int _wordSetQuantity;
volatile int _isCmdComplete;

void setup()
{
  // PC UART Init
  pinMode(0, INPUT);         // sets the digital pin as input
  pinMode(1, OUTPUT);        // sets the digital pin as output

  // Speech Recognition LED Status
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  // SR UART Init
  pinMode(11, INPUT);        // sets the digital pin as input
  pinMode(12, OUTPUT);       // sets the digital pin as output

  attachInterrupt(0, resetSROnInterrupt, LOW);
  Serial.begin(9600);
  delay(200);

  _sRDetect = FALSE;
  resetWordSetState();

  // Set up speech recognition
  SR_setup();

  if (!SR_Detect())
  {
    _sRDetect = FALSE;
    digitalWrite(errorStatusPin, HIGH);
    //Serial.println("SR NA");
  }
  else {
    _sRDetect = TRUE;
    digitalWrite(readyStatusPin, HIGH);
    //Serial.println("SR OK");
    // Set robot timeout to 2 seconds
    SR_SetTimeout(1);
    delay(200);
    // Set SR language to English
    SR_SetLanguage(0);
  }
}

void loop()
{
  if(_sRDetect==TRUE)
  {
    SI_Recognition();
  }
}

void resetSROnInterrupt()
{
  _wordSet = 1;
  _wordSetVerb = STOP_CMD; //STOP
  _wordSetDirection = 0;
  _wordSetQuantity = 0;
  digitalWrite(wordSetThreePin, LOW);
  digitalWrite(wordSetTwoPin,   LOW);
  digitalWrite(wordSetOnePin,   LOW);
  digitalWrite(wordSetZeroPin,  LOW);
}

void resetStatusLEDs()
{
  digitalWrite(wordSetThreePin, LOW);
  digitalWrite(wordSetTwoPin,   LOW);
  digitalWrite(wordSetOnePin,   LOW);
  digitalWrite(wordSetZeroPin,  LOW);
}

void resetWordSetState()
{
  _wordSet = 1;
  _wordSetVerb = STOP_CMD; //STOP
  _wordSetDirection = 0;
  _wordSetQuantity = 0;
}

void sendCmdToRobot()
{
  Serial.print(START_CMD);
  Serial.print(_wordSetVerb);
  if(_wordSet >= 2)
    Serial.print(_wordSetDirection);
  if(_wordSet == 3)
    Serial.print(_wordSetQuantity, HEX);
  Serial.println(END_CMD);
  Serial.flush();
  if(_wordSetVerb == LOOK_CMD) // Wait for sensory data
  {
    while(1)
    if(Serial.available() > 0)
    {
      int incomingByte = Serial.read();
      if(incomingByte == END_CMD)
        break;
      Serial.print((char)incomingByte);
    }
  }
}

void fadeReadyPin()
{
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(readyStatusPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(8);
  }

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5)
  {
    // sets the value (range from 0 to 255):
    analogWrite(readyStatusPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(8);
  }
}

void SI_Recognition()
{
  int cmd;

  if(_isCmdComplete == TRUE)
  {
    _isCmdComplete = FALSE;
    sendCmdToRobot();
    delay(200);
    resetStatusLEDs();
    resetWordSetState();
  }

  fadeReadyPin();
  SR_RecognizeSI(_wordSet);
  cmd = SR_CheckResult();
  //Serial.print(SPEAK_MSG);

  if(cmd < 0) //-1=timeout, -2=error
  {
    digitalWrite(errorStatusPin, HIGH);
    delay(200);
    digitalWrite(errorStatusPin, LOW);
    return;
    //if(cmd == -1)
    //  Serial.println(TIMEOUT_MSG);
    //else // error -2
    //  Serial.println(ERROR_MSG);
  }

  if((_wordSet == 3) && (cmd >= ZERO_CMD) && (cmd <= TEN_CMD))
  {
    _isCmdComplete = TRUE;
    _wordSetQuantity = cmd;
    digitalWrite(wordSetThreePin, HIGH);
  }

  if(_wordSet == 2)
  {
    switch(cmd)
    {
      case LEFT_CMD:
      case RIGHT_CMD:
      case FORWARD_CMD:
      case BACKWARD_CMD:
        _wordSetDirection = cmd;
        digitalWrite(wordSetTwoPin, HIGH);
        if(_wordSetVerb == RUN_CMD)
        {
          _isCmdComplete = TRUE;
          digitalWrite(wordSetThreePin, HIGH);
        }
        else
          _wordSet++;
        break;
      default:
        break;
    }
  }

  if(_wordSet == 1)
  {
    switch(cmd)
    {
      // 1 word sentence
      case ACTION_CMD:
      case LOOK_CMD:
      case STOP_CMD:
      case HELLO_CMD:
        _isCmdComplete = TRUE;
        _wordSetVerb = cmd;
        digitalWrite(wordSetZeroPin, HIGH);
        digitalWrite(wordSetOnePin, HIGH);
        digitalWrite(wordSetTwoPin, HIGH);
        break;

      // 2 word sentence
      case RUN_CMD:
      // 3 word sentence
      case MOVE_CMD:
        _wordSet++;
        _wordSetVerb = cmd;
        digitalWrite(wordSetZeroPin, HIGH);
        digitalWrite(wordSetOnePin, HIGH);
        break;

      default:
        break;
    }
  }
}

void SR_setup()
{
  _baudRate = 9600;
  _bitPeriod = 1000000 / _baudRate;
  _receivePin = 11;
  _transmitPin = 12;
  digitalWrite(_transmitPin, HIGH);
  delayMicroseconds(_bitPeriod);
}

unsigned char SR_read(void)
{
  uint8_t val = 0;
  int bitDelay = _bitPeriod - clockCyclesToMicroseconds(100);

  // one byte of serial data (LSB first)
  // ...--\    /--\/--\/--\/--\/--\/--\/--\/--\/--...
  //   \--/\--/\--/\--/\--/\--/\--/\--/\--/
  //  start  0   1   2   3   4   5   6   7 stop

  while (digitalRead(_receivePin));

  // confirm that this is a real start bit, not line noise
  if (digitalRead(_receivePin) == LOW) {
    // frame start indicated by a falling edge and low start bit
    // jump to the middle of the low start bit
    delayMicroseconds(bitDelay / 2 - clockCyclesToMicroseconds(50));

    // offset of the bit in the byte: from 0 (LSB) to 7 (MSB)
    for (int offset = 0; offset < 8; offset++) {
  // jump to middle of next bit
  delayMicroseconds(bitDelay);

  // read bit
  val |= digitalRead(_receivePin) << offset;
    }
    delayMicroseconds(_bitPeriod);
    return val;
  }
  return -1;
}

void SR_write(uint8_t b)
{
  if (_baudRate == 0)
    return;

  int bitDelay = _bitPeriod - clockCyclesToMicroseconds(50); // a digitalWrite is about 50 cycles
  byte mask;

  digitalWrite(_transmitPin, LOW);
  delayMicroseconds(bitDelay);

  for (mask = 0x01; mask; mask <<= 1)
{
    if (b & mask){ // choose bit
      digitalWrite(_transmitPin,HIGH); // send 1
    }
    else{
      digitalWrite(_transmitPin,LOW); // send 1
    }
    delayMicroseconds(bitDelay);
  }

  digitalWrite(_transmitPin, HIGH);
  delayMicroseconds(bitDelay);
}

unsigned char SR_Detect(void)
{
  unsigned char i;
  for (i = 0; i < 5; ++i) {
    delay(100);
    SR_write(CMD_BREAK);
    if ( SR_read() == STS_SUCCESS)
      return 255;
  }
  return 0;
}

unsigned char SR_SetLanguage(unsigned char lang)
{

  SR_write(CMD_LANGUAGE);
  delay(5);
  SR_write(ARG_ZERO + lang);

  if (SR_read() == STS_SUCCESS)
    return 255;
  return 0;
}

void SR_RecognizeSD(unsigned char group)
{
  SR_write(CMD_RECOG_SD);
  delay(5);
  SR_write(ARG_ZERO + group);
}

void SR_RecognizeSI(unsigned char ws)
{
  SR_write(CMD_RECOG_SI);
  delay(5);
  SR_write(ARG_ZERO + ws);
}

void SR_SetTimeout(unsigned char s)
{
  SR_write(CMD_TIMEOUT);
  delay(5);
  SR_write(ARG_ZERO + s);
  delay(5);
}

signed char SR_CheckResult(void)
{
  unsigned char rx;
  rx = SR_read();
  if (rx == STS_SIMILAR || rx == STS_RESULT) {
    delay(5);
    SR_write(ARG_ACK);
    return (SR_read() - ARG_ZERO);
  }
  if (rx == STS_TIMEOUT)
    return -1;

  return -2;
}
