#include "inoutils.h"
//TODO: Properly assign ints
#define B1 NULL
#define B2 NULL
#define B3 NULL
#define USTrig NULL
#define USEcho NULL
#define ERRLED NULL //Error Led
//Need movement functions to return true for decision tree format
int LookRight(MicroServo m,UltrasonicSensor us)
{
  m.SetAngle(0);
  return us.GetAngle();
}

int LookLeft(MicroServo m,UltrasonicSensor us)
{
  m.SetAngle(180);
  return us.GetAngle();
}

bool Reverse(Car c)
{
  c.setRight(-200);
  c.setLeft(-200);
  return true;
}

void Error(Led L)
{
  L.set(true); //turn on led
}



void setup() {

  //TODO: Properly assign ints to wheels
  int FR, FL, BR, BL;
  FR = FL = BR = BL = NULL;
  int speed = 200;
  int sPin = NULL;

  Button Btn1(B1);
  Button Btn2(B2);
  Button Btn3(B3);

  Car car(FR, FL, BR, BL, sPin, speed);


}

void loop() {
  // put your main code here, to run repeatedly:

}




