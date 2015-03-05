//Controls
/*
UL - Forward Left
US - Forward
UR - Forward Right
LS - Left Turn
RS - Right Turn
DL - Reverse Left
DS - Reverse
DR - Reverse Right

Buttons
AA - A Button
BB - B Button
CC - C Button
DD - D Button

ON - ON
OFF - OFF

End Command/Button Release - SS

Servos stop at 1500 write

*/

#include <Servo.h> //Servo Library

//BT Operations D-pad
#define _US 0x5553
#define _DS 0x4453
#define _LS 0x4C53
#define _RS 0x5253
#define _UL 0x554C
#define _DL 0x444C
#define _UR 0x5552
#define _DR 0x4452
#define _SS 0x5353
//BT Operations Letter Pad
#define _AA 0x4141
#define _BB 0x4242
#define _CC 0x4343
#define _DD 0x4444
//Servos
Servo servoLeft;
Servo servoRight;

//BT Command Parsing buffers
byte buff[2];
uint16_t command;

//"Simple" Hardware
int piezoPin = 11;
int IRRangerPin = A0;

//States
//TODO

void setup(){
  //Begin Serial Interface with BTShield
  Serial.begin(9600);
  //Attach Servo Logic
  servoLeft.attach(13);
  servoRight.attach(12);
  //Forward for .5sec
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(500);
  //Backwards for .5sec
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(500);
  //Stop Motion
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  //Delay 3 seconds then 1khz tone to indicates success
  delay(3000);
  tone(piezoPin, 1000, 1000);
}

void loop(){
  //LOGIC OVERRIDE IN SERIALEVENT()
  getRange();
}

void serialEvent(){
  //Wait for two bytes = two character codes sent from controller
  while(Serial.available() < 2);
  Serial.readBytes(buff, 2);
  command = (buff[0]<<8) | (buff[1]);
  if(command){
   switch(command){
    case _SS:  SSMove();break;
    case _UL:  ULMove();break;
    case _US:  USMove();break;
    case _UR:  URMove();break;
    case _LS:  LSMove();break;
    case _RS:  RSMove();break;
    case _DL:  DLMove();break;
    case _DS:  DSMove();break;
    case _DR:  DRMove();break;
    case _AA:  AAAction();break;
    case _BB:  BBAction();break;
    case _CC:  CCAction();break;
    case _DD:  DDAction();break;
    default: break;
   } 
  }
}
//Ranger
int getRange(){
 int raw = analogRead(IRRangerPin);
 Serial.println(String(raw));
 return raw;
}


//Begin Drive Logic
void SSMove(){
 servoLeft.writeMicroseconds(1500);
 servoRight.writeMicroseconds(1500);   
}
void ULMove(){
 servoLeft.writeMicroseconds(1600);
 servoRight.writeMicroseconds(1200);
}

void USMove(){
 servoLeft.writeMicroseconds(1700);
 servoRight.writeMicroseconds(1300); 
}

void URMove(){
 servoLeft.writeMicroseconds(1700);
 servoRight.writeMicroseconds(1300); 
}

void LSMove(){
 servoLeft.writeMicroseconds(1000);
 servoRight.writeMicroseconds(1000);
}

void RSMove(){
 servoLeft.writeMicroseconds(2000);
 servoRight.writeMicroseconds(2000); 
}

void DLMove(){
 servoLeft.writeMicroseconds(1300);
 servoRight.writeMicroseconds(1700);
}

void DSMove(){
 servoLeft.writeMicroseconds(1300);
 servoRight.writeMicroseconds(1700);
}

void DRMove(){
 servoLeft.writeMicroseconds(1700);
 servoRight.writeMicroseconds(1300);
}

//Begin Button Logic
void AAAction(){
  tone(piezoPin, 1000, 1000);
}

void BBAction(){
  tone(piezoPin, 2000, 1000);
}

void CCAction(){
  tone(piezoPin, 3000, 1000);
}

void DDAction(){
  tone(piezoPin, 4000, 1000);
}

//Simple Hardware Functions

