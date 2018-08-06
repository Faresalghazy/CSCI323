#include "inoutils.h"
//TODO: Properly assign ints
#define B1 0
#define B2 0
#define B3 0
#define MSPIN 0 //MicroServo
#define USTrig 0
#define USEcho 0
#define ERRLED 0 //Error Led
int FR, FL, BR, BL;
int speed = 200;
int sPin = NULL;
int LeftDist1, LeftDist2, RightDist1, RightDist2; //Dist=distance
bool pressed1, pressed2, pressed3;
Button Btn1(B1);
Button Btn2(B2);
Button Btn3(B3);
Car car(FR, FL, BR, BL, sPin, speed);
UltrasonicSensor USS(USTrig, USEcho);
MicroServo ms(MSPIN, 90);
Led led(NULL);

bool LookRight(MicroServo m)
{
  m.SetAngle(0);
  return true;

}

void LookLeft(MicroServo m)
{
  m.SetAngle(180);
}
void Lookleft(MicroServo m)
{
  m.SetAngle(180);
}
bool void LookAhead(MicroServo m)
{
  m.SetAngle(90);
  return True;
}
void Error(Led L)
{
  L.set(true); //turn on led
}

void Forward(Car c)
{
  c.setRight(200);
  c.setLeft(200);
}

void Stop(Car c)
{
  c.setRight(00);
  c.setLeft(00);
}

bool thereIsParking(int dist1, int dist2);
{
  return ((dist2 - dist1) / dist1) >= 0.1
}

bool RevParkPos(car)
{
  car.setRight(150);
  delay(200);
  Stop(car);
}
bool Reverse(car)
{
  car.setRight(-200);
  car.setLeft(-200);
}
void setup() {
  //TODO: Properly assign ints to wheels
  FR = FL = BR = BL = NULL;


  pressed1 = pressed2 = pressed3 = false;
  LookLeft(ms);
}

void loop() {
  pressed1 = Btn2.Get();
  pressed2 = Btn2.Get();
  pressed3 = Btn3.Get();
  //only one button should be pressed
  if (pressed1 && pressed2 || pressed1 && pressed2 || pressed2 && pressed3)
    Error(led);


  //seq1
  if (pressed1)
  {
    LeftDist1 = USS.GetDistance();
    delay(300);
    Forward(car);
    delay(1000);
    Stop(car);
    LeftDist2 = USS.GetDistance();
    delay(300);

    if (thereIsParking(dist1, dist2))
    {
      Forward(car);
      //TODO test this value with arduino
      delay(500);
      Stop(car);
      if ( RevParkPos(car))
      {
        if (Reverse)
        {
          if (Collision)
          {
            Error(led);
          }
        }
        else {
          Error(led);
        }
      }
      else
      {
        Error(led);
      }
    }
  }

  //seq2
  if (pressed2)
  {
    if (LookAhead(ms))
    {
      if (Lookleft(ms))
      {
        Forward(car);
        delay(300);
        car.setRight(200);
        delay(300);
        Stop(car);
        Forward(car);
        delay(3000);
        Stop(car);
      }
      else {
        Error(led);
      }
    }
    else {
      Error(led);
    }
  }

  //seq3
  if (pressed3)
  {
    if (LookAhead(ms))
    {
      if (Lookleft(ms))
      {
        if (LookRight(ms)
      {
        Forward(car);
          delay(300);
          car.setLeft(200);
          delay(300);
          Stop(car);
          Forward(car);
          delay(3000);
          Stop(car);
        }
        else
        {
          Error(led);
        }
      }
      else {
        Error(led);
      }
    }
    else {
      Error(led);
    }
  }
}




