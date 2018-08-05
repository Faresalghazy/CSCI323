/*
   OOP library for common arduino I/O devices
   Made by Thomas Toth
   Car class by Fares Al Ghazy
*/

#ifndef ARDUINO_UTILS
#define ARDUINO_UTILS

#include<Servo.h>

class Wheel
{ private:
    int m1Pin;		//Digital pin for the motor direction
    int m2Pin;		//Digital pin for the motor direction
    int sPin;		//Digital pin for controlling the speed
    int mSpeed;		//Speed of the movement (-255 -> 255)


  public:
    //Creates a Wheel object with 2 pins for direction and 1 analog pin for speed.
    //Stores the speed(-255 -> 255), where negative values indicate reverse direction.
    Wheel(int pm1, int pm2, int ps, int ws);
    void setValues(int pm1, int pm2, int ps, int ws);
    Wheel();

    //Sets the movement direction and speed of the wheel motor. Speed is passed as an absolute value
    //Positive speed means forward, negative speed means reverse movement.
    void SetMovement(int ms);

    //Gets the speed the wheel is turning with.
    int GetSpeed();
};



class UltrasonicSensor
{ private:
    int tPin;   //Digital trigger pin of the sensor
    int ePin;   //Digital echo pin of the sensor


  public:
    //Creates an UltrasonicSensor object with a trigger and an echo pin parameter.
    //Trigger pin is set to OUTPUT, Echo pin is set to INPUT
    UltrasonicSensor(int pt, int pe);

    //Calculates the distance between the sensor and the obstacle in front of it.
    //Sets the trigger to LOW for 2 microseconds, then HIGH for 10 microseconds.
    int GetDistance();
};



class LED
{ private:
    int pin; 	//Digital pin of the LED
    int state;	//State of the LED, HIGH or LOW


  public:
    //Creates an LED object with an associated pin, and a state of HIGH or LOW.
    //States correspond to booleans. Constructor allows for custom start state, LOW be default.
    LED(int pin, int state);

    //Sets the state of the LED to HIGH if passed true, LOW is passed false.
    void Set(bool);

    //Returns if the LED is turned on, ie the state is HIGH.
    bool IsOn();
};



class MicroServo
{ private:
    Servo srv;  //Instance of an arduino Servo class
    int angle;   //Angle of the servo's facing
    int sPin;    //Pin where the servo is connected

  public:
    //Creating a servo instance
    ServoMotor(int angle, int sp);

    //Setting the angle
    void SetAngle(int angle);

    //Getting the angle
    void GetAngle(int angle);
};



class Button
{ private:
    int pin;		//Digital pin of the button

  public:
    Button(int pin);
    bool Get();
};

class Car
{
  private:
    Wheel Right, Left;

  public:

    Car(int FR, int FL, int BR, int BL , int sPin, int mSpeed); //FRONT RIGHT, FRONT LET, BACK RIGHT, BACK LEFT

    void setRight(int speed);

    void setLeft(int speed);
};

#endif
