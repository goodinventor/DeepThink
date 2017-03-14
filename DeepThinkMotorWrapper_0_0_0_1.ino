//
// DeepThinkMotorWrapper 0.0.0.1
//
// programmed by George Andrews
//
// This program runs on the 86Duino One in the DeepThink project.
// It receives messages over Serial from the host (the Raspberry
// Pi 3) and follows commands accordingly (regarding the four
// servos under its control). The Raspberry Pi 3 does the image
// processing and then outputs commands to the 86Duino One.
//
// The servos used are from the Meccanoid G15 robot (hence the
// MeccaBrain library is used).
//

//
// Section 1 - Included Headers
//
#include "MeccaBrain_86Duino_0_0_0_1.h"

//
// Section 2 - Variables
//

//
// Section 2a - Servo Pins
//
#define RightElbowServoPin 21
#define RightShoulderServoPin 22
#define LeftElbowServoPin 23
#define LeftShoulderServoPin 24

//
// Section 2b - Servo Objects
//
// NOTE: The servo objects correspond to the below pins.
//
// RightElbowServo: 21
// RightShoulderServo: 22
// LeftElbowServo: 23
// RightElbowServo: 24
//
MeccaBrain RightElbowServo(RightElbowServoPin);
MeccaBrain RightShoulderServo(RightShoulderServoPin);
MeccaBrain LeftElbowServo(LeftElbowServoPin);
MeccaBrain LeftShoulderServo(LeftShoulderServoPin);

//
// Section 2c - Timing-Related Variables
//
unsigned long previousMillis = 0;

//
// Section 3 - Functions
//

//
// Section 3a - Servo-Related Functions
//
void MoveRightForearmUp(int Position, int Speed)
{
  // servo will be turning counter-clockwise
  for (int i = RightElbowServo.getServoPosition(0); i < Position; i += Speed)
  {
    RightElbowServo.setServoPosition(0, i);
    RightElbowServo.communicate();
  }
}

void MoveRightForearmDown(int Position, int Speed)
{
  // servo will be turning clockwise
  for (int i = RightElbowServo.getServoPosition(0); i > Position; i -= Speed)
  {
    RightElbowServo.setServoPosition(0, i);
    RightElbowServo.communicate();
  }
}

void MoveLeftForearmUp(int Position, int Speed)
{
  // servo will be turning clockwise
  for (int i = LeftElbowServo.getServoPosition(0); i > Position; i += Speed)
  {
    LeftElbowServo.setServoPosition(0, i);
    LeftElbowServo.communicate();
  }
}

void MoveLeftForearmDown(int Position, int Speed)
{
  // servo will be turning counter-clockwise
  for (int i = LeftElbowServo.getServoPosition(0); i < Position; i -= Speed)
  {
    LeftElbowServo.setServoPosition(0, i);
    LeftElbowServo.communicate();
  }
}

//
// Section 3b - Serial-Related Functions
//
void ReadSerialAndRespond()
{
  // check to see if any bytes are available for reading
  if (Serial.available() > 0)
  {
    //
    // Below is the table of values corresponding to each of the
    // commands.
    //
    // MoveRightForearmUp - a [position] [speed]
    // MoveRightForearmDown - b [position] [speed]
    // MoveLeftForearmUp - c [position] [speed]
    // MoveLeftForearmDown - d [position] [speed]
    //
    
    // look for the command
    char command = Serial.read();
    
    switch (command)
    {
      case 'a':
      {
        // now look for valid integers of positions and then speed
        int APosition = Serial.parseInt();
        int ASpeed = Serial.parseInt();
        
        // look for newline which signifies the end of the command
        if (Serial.read() == '\n')
        {
          // execute the command
          MoveRightForearmUp(APosition, ASpeed);
          
          // we are done with the command, now send back a message
          // to tell the Raspberry Pi 3 that we are ready for a
          // new command
          Serial.println(F("D"));
        }
        break;
      }
      
      case 'b':
      {
        // now look for valid integers of positions and then speed
        int BPosition = Serial.parseInt();
        int BSpeed = Serial.parseInt();
        
        // look for newline which signifies the end of the command
        if (Serial.read() == '\n')
        {
          // execute the command
          MoveRightForearmDown(BPosition, BSpeed);
          
          // we are done with the command, now send back a message
          // to tell the Raspberry Pi 3 that we are ready for a
          // new command
          Serial.println(F("D"));
        }
        break;
      }
      
      case 'c':
      {
        // now look for valid integers of positions and then speed
        int CPosition = Serial.parseInt();
        int CSpeed = Serial.parseInt();
        
        // look for newline which signifies the end of the command
        if (Serial.read() == '\n')
        {
          // execute the command
          MoveLeftForearmUp(CPosition, CSpeed);
          
          // we are done with the command, now send back a message
          // to tell the Raspberry Pi 3 that we are ready for a
          // new command
          Serial.println(F("D"));
        }
        break;
      }
      
      case 'd':
      {
        // now look for valid integers of positions and then speed
        int DPosition = Serial.parseInt();
        int DSpeed = Serial.parseInt();
        
        // look for newline which signifies the end of the command
        if (Serial.read() == '\n')
        {
          // execute the command
          MoveLeftForearmDown(DPosition, DSpeed);
          
          // we are done with the command, now send back a message
          // to tell the Raspberry Pi 3 that we are ready for a
          // new command
          Serial.println(F("D"));
        }
        break;
      }
    }
  }
}

//
// Section 3c - Timing-Related Functions
//
boolean WaitMillis(long interval)
{
  // check to see if it's time
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval)
  {
    // save last time
    previousMillis = currentMillis;
    
    return true;
  }
  
  return false;
}

//
// Section 4 - Setup
//
void setup()
{
  // initialize Serial
  Serial.begin(9600);
  
  while (!Serial)
  {
    ; // wait for serial port to connect
  }
}

//
// Section 5 - Loop
//
void loop()
{
  ReadSerialAndRespond();
  
  // wait a small amount (10 milliseconds of time before looping
  // again
  do
  {
    ; // waiting...
  } while (!WaitMillis(10));
}
