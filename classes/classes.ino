/*
   OOP library for common arduino I/O devices
   Made by Thomas Toth
   Car class by Fares Al Ghazy
*/


#include<math.h>
#include<stdlib.h>

int x = rand();



//--------------------------------------------------------------------------//
//----------------------------- Random Library -----------------------------//
//--------------------------------------------------------------------------//

class RandomClass
{ public:

    RandomClass(int seed = millis())
    { randomSeed(seed);
    }

    static void SetSeed(int seed)
    { randomSeed(seed);
    }

    static long Range( int rMax, int rMin = 0)
    { return random(rMin, rMax);
    }
};

RandomClass Random;



//--------------------------------------------------------------------------//
//------------------------------ Time Library ------------------------------//
//--------------------------------------------------------------------------//

class TimeLib
{ public:

    long execTime;   //Execution time since the beginning in milliseconds
    int  pastTime;   //The previous time in milliseconds
    int  timeScale;  //Scale of the delta time
    int  deltaTime;  //Time between the current and previous update scaled
    int  uDeltaTime; //Time between the current and previous update unscaled

    TimeLib()
    { this->execTime   = 0;
      this->pastTime   = millis();
      this->timeScale  = 1;
      this->deltaTime  = 0;
      this->uDeltaTime = 0;
    }

    void Tick()
    { int currentTime = millis();
      uDeltaTime = currentTime - pastTime;

      if (uDeltaTime < 0)
        uDeltaTime += 1000;

      deltaTime = uDeltaTime * timeScale;
      execTime += uDeltaTime;
      pastTime = currentTime;

    }
};

TimeLib Time;



//--------------------------------------------------------------------------//
//------------------------------ Wheel Library -----------------------------//
//--------------------------------------------------------------------------//

class Wheel
{ public:

    int m1Pin;    //Digital pin for the motor direction
    int m2Pin;    //Digital pin for the motor direction
    int sPin;   //Digital pin for controlling the speed
    int mSpeed;   //Speed of the movement (-255 -> 255)

    Wheel() {}

    Wheel(int pm1, int pm2, int ps, int ws)
    { this->m1Pin = pm1;
      this->m2Pin = pm2;
      this->sPin  = ps;

      pinMode(this->m1Pin, OUTPUT);
      pinMode(this->m2Pin, OUTPUT);
      SetMovement(ws);
    }
    

    //Sets the movement direction and speed of the wheel motor.
    void SetMovement(int ms)
    { this->mSpeed = ms;

      analogWrite (this->sPin, this->mSpeed < 0 ? -this->mSpeed : this->mSpeed);
      digitalWrite(this->m1Pin, (this->mSpeed > 0 ? HIGH : LOW) );
      digitalWrite(this->m2Pin, (this->mSpeed < 0 ? HIGH : LOW) );
    }
};

//--------------------------------------------------------------------------//
//--------------------------- Car Library 2 ----------------------------------//
//--------------------------------------------------------------------------//

class Car
{
  private:
    Wheel Right, Left;

  public:
    Car(Wheel Right, Wheel Left)
    {
      this->Right = Right;
      this->Left = Left;
    }

    void setRight(int speed) {
      Right.SetMovement(speed);
    }

    void setLeft(int speed) {
      Left.SetMovement(speed);
    }
};


//--------------------------------------------------------------------------//
//--------------------------- Ultrasonic Library ---------------------------//
//--------------------------------------------------------------------------//

class UltrasonicSensor
{ public:

    int tPin;   //Trigger pin of the sensor
    int ePin;   //Echo pin of the sensor

    UltrasonicSensor(int pt, int pe)
    { this->tPin = pt;
      this->ePin = pe;

      pinMode(this->tPin, OUTPUT);
      pinMode(this->ePin, INPUT );
    }

    //Calculates the distance between the sensor and the obstacle in front of it.
    //Sets the trigger to LOW for 2 microseconds, then HIGH for 10 microseconds.
    int GetDistance()
    {
      digitalWrite(tPin, LOW);
      delayMicroseconds(2);

      digitalWrite(tPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(tPin, LOW);

      int duration = pulseIn(ePin, HIGH);
      return duration * 0.034 / 2;
    }
};



//--------------------------------------------------------------------------//
//------------------------------ Car Library -------------------------------//
//--------------------------------------------------------------------------//
/*
class Car
{ public:

    Wheel rightWheel;
    Wheel leftWheel;
    int   maxSpeed;

    Car(int ls, int ld, int rs, int rd, int sp) : leftWheel(ld, ls, sp, 0), rightWheel(rd, rs, sp, 0)
    { this->maxSpeed = sp;
    }

    void Stop()
    { this->leftWheel.SetMovement (0, 0);
      this->rightWheel.SetMovement(0, 0);
    }

    void Forward()
    { this->leftWheel.SetMovement (this->maxSpeed, 0);
      this->rightWheel.SetMovement(this->maxSpeed, 0);
    }

    void Reverse()
    { this->leftWheel.SetMovement (this->maxSpeed, 1);
      this->rightWheel.SetMovement(this->maxSpeed, 1);
    }

    void TurnRight()
    { this->leftWheel.SetMovement (this->maxSpeed, 0);
      this->rightWheel.SetMovement(this->maxSpeed, 1);
    }

    void TurnLeft()
    { this->leftWheel.SetMovement (this->maxSpeed, 1);
      this->rightWheel.SetMovement(this->maxSpeed, 0);
    }

    void SteerLeftF()
    { this->leftWheel.SetMovement (this->maxSpeed / 2, 0);
      this->rightWheel.SetMovement(this->maxSpeed,   0);
    }

    void SteerLeftR()
    { this->leftWheel.SetMovement (this->maxSpeed / 2, 0);
      this->rightWheel.SetMovement(this->maxSpeed,   0);
    }

    void SteerRightF()
    { this->leftWheel.SetMovement (this->maxSpeed,   0);
      this->rightWheel.SetMovement(this->maxSpeed / 2, 0);
    }

    void SteerRightR()
    { this->leftWheel.SetMovement (this->maxSpeed,   0);
      this->rightWheel.SetMovement(this->maxSpeed / 2, 0);
    }
};


*/

//--------------------------------------------------------------------------//
//----------------------------- Servo Library ------------------------------//
//--------------------------------------------------------------------------//

class ServoMotor
{
    //SoftwareServo servo;
    int angle;
    int sPin;

    //ServoMotor(int angle, int sp)
    //{ this->angle = angle;
    //  this->sPin  = sp;
    //
    //  servo.attach(sp);
    //  servo.write(angle);
    //}

    //void SetAngle(int angle)
    //{
    //  this->angle = angle;
    //  servo.write(angle);
    //}


};



//--------------------------------------------------------------------------//
//---------------------------- ARDUINO PROGRAM -----------------------------//
//--------------------------------------------------------------------------//

void setup()
{
}

void loop()
{
  Time.Tick();
}
