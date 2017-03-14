//
// MeccaBrain 86Duino 0.0.0.1
//
// NOTE: This library is heavily based on the MeccaBrain library
// provided at http://www.meccano.com/meccanoid-opensource with a
// few modifications. Below details the changes.
//
// servo1Positions[], servo2Positions[], servo3Positions[], and
// servo4Positions[] are removed because the 86Duino Coding 300
// compiler for the 86Duino One does not support array
// declarations of the type "int servo1Positions[]" and also
// because those arrays are never used in the code.
//
// inputBytes[] and inputBytesInfo() are also removed because they
// are never used in the code either.
//
#ifndef MeccaBrain_86Duino_0_0_0_1_h
#define MeccaBrain_86Duino_0_0_0_1_h

#include "Arduino.h"

class MeccaBrain{
  public:
    MeccaBrain(int pin);
    
    byte outputByteInfo(int num);
    byte inputByteInfo();
    byte checkSumByteInfo();
    byte servoPositionsInfo(int servoNum);
    char moduleTypeInfo(int num);
    byte moduleNumInfo();
    byte getLEDorder();
    byte getLEDbyte1();
    byte getLEDbyte2(); 

    void setLEDColor(byte red, byte green, byte blue, byte fadetime);
    void setServoColor(int servoNum, byte color);
    void setServoPosition(int servoNum, byte pos);
    void setServotoLIM(int servoNum);
    byte getServoPosition(int servoNum);
    
    void communicate();   
    void sendByte(byte servoData);
    byte receiveByte();
    byte calculateCheckSum(byte Data1, byte Data2, byte Data3, byte Data4);
    
  private:
    int _pmwPin;
    int servoNumber;
    int inputCounter = 0;
    int moduleNum = 0;
    int printModNum = 0;
    int ledOrder = 0;
    int bitDelay = 417;
    int receiveArray[8];
    
    byte inputByte;
    byte checkSum;
    byte servoPos;
    byte LEDoutputByte1 = 0x00;
    byte LEDoutputByte2 = 0x47;
    byte header = 0xFF;
    byte outputByte[4];
    byte printOutputByte[4];
    
    char moduleType[4];
    
};

#endif
