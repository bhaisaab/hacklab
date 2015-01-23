#include <SoftwareSerial.h>

SoftwareSerial lcdSerial(10, 11); // RX, TX

void setup()
{
  Serial.begin(9600);
  lcdSerial.begin(9600);
  lcdSerial.write(23);
  lcdSerial.write("    ArduLCD    \r");
  lcdSerial.write(" rohityadav.in \r");
}

void loop()
{
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
    if (incomingByte == '~') {
      Serial.print('\\');
      incomingByte = 1;
    }
    else if (incomingByte == '\\') {
      Serial.print('~');
      incomingByte = 0;
    }
    lcdSerial.write(incomingByte);      
  }
}
