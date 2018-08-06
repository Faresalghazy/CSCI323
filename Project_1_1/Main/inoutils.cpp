/*
   OOP library for common arduino I/O devices
   Made by Tamas Toth
   Car class by Fares Al Ghazy
*/

#include "inoutils.h"
#include "Arduino.h"
#include <Servo.h>

UltrasonicSensor::UltrasonicSensor(int pt, int pe)
{ this->tPin = pt;
  this->ePin = pe;

  pinMode(this->tPin, OUTPUT);
  pinMode(this->ePin, INPUT );
}

int UltrasonicSensor::GetDistance()
{ digitalWrite(tPin, LOW);
  delayMicroseconds(2);

  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);

  int duration = pulseIn(ePin, HIGH);
  return duration * 0.034 / 2;
}

LED::LED(int pin, int state)
{ this->pin = pin;

  pinMode(this->pin, OUTPUT);
  Set(state);
}

void LED::Set(bool state)
{ this->state = state ? HIGH : LOW;
  digitalWrite(this->pin, this->state);
}

bool LED::IsOn()
{ return this->state == HIGH ? true : false;
}

Wheel:: Wheel(int pm1, int pm2, int ps, int ws)
{ this->m1Pin = pm1;
  this->m2Pin = pm2;
  this->sPin  = ps;

  pinMode(this->m1Pin, OUTPUT);
  pinMode(this->m2Pin, OUTPUT);
  SetMovement(ws);
}

void Wheel::SetMovement(int ms)
{ this->mSpeed = ms;

  analogWrite (this->sPin, this->mSpeed < 0 ? -this->mSpeed : this->mSpeed);
  digitalWrite(this->m1Pin, (this->mSpeed > 0 ? HIGH : LOW) );
  digitalWrite(this->m2Pin, (this->mSpeed < 0 ? HIGH : LOW) );
}

int Wheel::GetSpeed()
{ return this->mSpeed;
}
void Wheel::setValues(int pm1, int pm2, int ps, int ws)
{
  this->m1Pin = pm1;
  this->m2Pin = pm2;
  this->sPin  = ps;

  pinMode(this->m1Pin, OUTPUT);
  pinMode(this->m2Pin, OUTPUT);
  SetMovement(ws);

}
MicroServo:: MicroServo(int pin, int angle)
{ this->angle = angle;
  this->sPin  = pin;

  srv.attach(pin);
  srv.write(angle);
}


void MicroServo::SetAngle(int angle)
{ this->angle = angle;
  srv.write(angle);
}

int MicroServo::GetAngle(int angle)
{ return this->angle;
}

bool MicroServo::TurnRight()
{   srv.write(0);
    return true;
}

bool MicroServo::TurnLeft()
{   srv.write(180);
    return true;
}

bool MicroServo::TurnFront()
{   srv.write(90);
    return true;
}


Button::Button(int pin)
{ this->pin = pin;
  pinMode(this->pin, INPUT);
}

bool Button::Get()
{ return digitalRead(this->pin) == HIGH;
}

Car::Car(int FR, int FL, int BR, int BL , int LW1, int LW2, int LWS, int RW1, int RW2, int RWS) :
right(RW1, RW2, RWS), left(LW1, LW2, LWS), frontRight(FR), frontLeft(FL), backRight(BR), backLeft(BL)
{
  
}

void Car::setRight(int speed) {
  right.SetMovement(speed);
}

void Car::setLeft(int speed) {
  left.SetMovement(speed);
}
