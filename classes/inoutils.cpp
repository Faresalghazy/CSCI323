#include "inoutils.h"
#include "Arduino.h"

UltrasonicSensor::UltrasonicSensor(int pt, int pe)
{	this->tPin = pt;
  this->ePin = pe;

  pinMode(this->tPin, OUTPUT);
  pinMode(this->ePin, INPUT );
}

int UltrasonicSensor::GetDistance()
{	digitalWrite(tPin,LOW);
	delayMicroseconds(2);

	digitalWrite(tPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(tPin,LOW);

	int duration = pulseIn(ePin, HIGH);
	return duration * 0.034 / 2;
}

LED::LED(int pin, int state = false)
{	this->pin = pin;

	pinMode(this->pin, OUTPUT);
	Set(state);
}

void LED::Set(bool state)
{	this->state = state ? HIGH : LOW;
	digitalWrite(this->pin, this->state);
}

bool LED::IsOn()
{	return this->state == HIGH ? true : false;
}

Wheel::Wheel(int pm1, int pm2, int ps, int ws)
{ this->m1Pin = pm1;
	this->m2Pin = pm2;
	this->sPin  = ps;
	
	pinMode(this->m1Pin, OUTPUT);
	pinMode(this->m2Pin, OUTPUT);
	SetMovement(ws);
}

void Wheel::SetMovement(int ms)
{	this->mSpeed = ms;

	analogWrite (this->sPin, this->mSpeed < 0 ? -this->mSpeed : this->mSpeed);
	digitalWrite(this->m1Pin, (this->mSpeed > 0 ? HIGH : LOW) );
	digitalWrite(this->m2Pin, (this->mSpeed < 0 ? HIGH : LOW) );
}

int Wheel::GetSpeed() 
{	return this->mSpeed;
}

ServoMotor::ServoMotor(int angle, int sp)
{ this->angle = angle;
  this->sPin  = sp;
  
  srv.attach(sp);
  srv.write(angle); 
}

void ServoMotor::SetAngle(int angle)
{ this->angle = angle;
  srv.write(angle);
}

void ServoMotor::GetAngle(int angle)
{ return this->angle;
}

Button::Button(int pin)
{	this->pin = pin;
	pinMode(this->pin, INPUT);
}

bool Button::Get()
{	return digitalRead(this->pin) == HIGH;
}
