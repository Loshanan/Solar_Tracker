#include <Servo.h>

Servo xServo, yServo;
//xServo - for base

int ldrTLpin = A1; // top-left LDR
int ldrTRpin = A2; // top-right LDR
int ldrBLpin = A3; // bottom-left LDR
int ldrBRpin = A4; // bottom-right LDR

int TLval, TRval, BLval, BRval; //values readed from ldr sensors

int xServoPin = 5; // X-axis servo motor pin
int yServoPin = 6; // y axis servo motor pin

int threshold=100; //threshold value of changing the position of the tracker
int degree=2; //minimum degree that servo changes for an observation
int oldval; //rading value from servo motor

void rotate_servo(Servo motor, int rotation); 
void setup() {
  // put your setup code here, to run once:
xServo.attach(xServoPin);
yServo.attach(yServoPin);
pinMode(xServoPin, OUTPUT);
pinMode(yServoPin, OUTPUT);

//initial positions
xServo.write(90);
yServo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:


//reading analog values from ldr sensors
TLval = analogRead(ldrTLpin);
TRval = analogRead(ldrTRpin);
BLval = analogRead(ldrBLpin);
BRval = analogRead(ldrBRpin);

//calculating average values
int avgtop = (TLval + TRval)/2;
int avgbot = (BLval + BRval)/2;
int avgright = (TRval + BRval)/2;
int avgleft = (TLval + BLval)/2;

//calculating difference values
int dify = avgtop - avgbot;
int difx = avgright - avgleft;


//setting up X-axis
if (abs(difx)>=threshold){
  if(yServo.read()<=90){
    if (difx>0){rotate_servo(xServo, -1);}
    else{rotate_servo(xServo, +1);}
  }
  else{
    if (difx>0){rotate_servo(xServo, +1);}
      else{rotate_servo(xServo, -1);}
  }
}

//setting up Y-axis
if (abs(dify)>=threshold){
  if (dify>0){rotate_servo(yServo, -1);}
  else{rotate_servo(yServo, +1);}
}
delay(100);
}


void rotate_servo(Servo motor, int rotation){
  //rotation +1 for positive site rotation
  //rotation -1 for negetive site rotation
  oldval = motor.read();
  motor.write(oldval + rotation*degree);
}
