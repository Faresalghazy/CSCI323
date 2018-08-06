//Changelog 1.0 (Fares)
//Fares created the base code for parking logic

//Changelog 1.1 (Tamas)
//Moved the functions looking left, right and forward to the MicroServo class in "inoutils"
//Reformatted the initial #define, variable and object definitions +commented
//Changed the name of the variable "speed" to "dSpeed" due to possible arduino conflicts
//Changed Forward and Reverse functions to use the default speed variable, not hardcoded nubmers
//Defined pins for the Wheels and the 4 IR sensors
//Deleted default constructor of Wheels and re-wrote Car constructor to initialize wheels properly
//Fixed constructor for wheels in car class
//Added Infrared data members into car class
//Changed indentations to 4 spaces, cause screw 2 spaces, it gives me cancer
//Changed Button #defines B1, B2, B3 for conflicting with "Arduino.h"
//Added default value to many constructors in "inoutils.h"

#include "inoutils.h" 



//TODO: Properly assign pin IDs
#define Bt1 0       //Pin for Button1
#define Bt2 0       //Pin for Button2
#define Bt3 0       //Pin for Button3
#define IRFR 0      //Pin for the Front Right Infra-Red
#define IRFL 0      //Pin for the Front Left Infra-Red
#define IRBR 0      //Pin for the Back Right Infra-Red
#define IRBL 0      //Pin for the Back Left Infra-Red
#define USTrig 0    //Pin for Ultrasonic Trigger
#define USEcho 0    //Pin for Ultrasonic Echo
#define MSPIN  0    //Pin for Micro Servo
#define ERRLED 0    //Pin for LED showing errors
#define LeftW1 0    //Pin 1 for Left Wheel's direction
#define LeftW2 0    //Pin 2 for Left Wheel's direction
#define LeftWS 0    //Pin for Left Wheel's speed
#define RightW1 0   //Pin 1 for Right Wheel's direction
#define RightW2 0   //Pin 2 for Right Wheel's direction
#define RightWS 0   //Pin for Right Wheel's speed

#define Collision false

bool pressed1 = false;      //Pressed state of Button1
bool pressed2 = false;      //Pressed state of Button2
bool pressed3 = false;      //Pressed state of Button3
int dSpeed = 200;           //Default speed of the wheels

int FR = 0;     //Value of the Front Right Infrared Sensor
int FL = 0;     //Value of the Front Left Infrared Sensor
int BR = 0;     //Value of the Back Right Infrared Sensor
int BL = 0;     //Value of the Back Left Infrared Sensor

int LeftDist1 = 0;  //Last measured distance to the left
int LeftDist2 = 0;  //Current measured distance to the left

//Create objects for connected pieces
Button Btn1(Bt1);
Button Btn2(Bt2);
Button Btn3(Bt3);
UltrasonicSensor USS(USTrig, USEcho);
MicroServo ms(MSPIN, 180);
LED led(ERRLED);
Car car(IRFR, IRFL, IRBR, IRBL, LeftW1, LeftW2, LeftWS, RightW1, RightW2, RightWS);





//Sets the car to move in a forward direction
//Speed of the movement is set to be the default speed "dSpeed"
bool Forward()
{
    car.setRight(dSpeed);
    car.setLeft (dSpeed);
    return true;
}

//Sets the car to move in a reverse direction
//Speed of the movement is set to be the default speed "dSpeed"
bool Reverse()
{
    car.setRight(-dSpeed);
    car.setLeft(-dSpeed);
    return true;
}

//Stops the car by setting the speed to 0
bool Stop()
{
    car.setRight(0);
    car.setLeft (0);
    return true;
}


//Takes an LED object and turns it on
//The LED signals an error that happens during code execution
void Error()
{
    led.Set(true);
}


//Uses previously and currently measured distance by the Ultrasonic sensor
//Returns true if there is a parking space identified.
bool IsThereParking(int dist1, int dist2)
{
    return ((dist2 - dist1) / dist1) >= 0.1;
}

//Idk what iz dis
bool RevParkPos()
{
    car.setRight(150);
    delay(200);
    Stop();
}


void setup() 
{
}

void loop() 
{
    pressed1 = Btn1.Get();
    pressed2 = Btn2.Get();
    pressed3 = Btn3.Get();
    
    //Turn on the error light if more than one button is pressed at the time
    if ( (pressed1 && pressed2) || (pressed1 && pressed3) || (pressed2 && pressed3) )
    {
        Error();
    }


    //Sequence 1, searches for a parking space and parks.
    if (pressed1)
    {
        LeftDist1 = USS.GetDistance();
        delay(300);
        Forward();
        delay(1000);
        Stop();
        LeftDist2 = USS.GetDistance();
        delay(300);
  
        if (IsThereParking(LeftDist1, LeftDist2))
        {
            Forward();
            //TODO test this value with arduino
            delay(500);
            Stop();
            
            if ( RevParkPos())
            {   
                if (Reverse)
                {   
                    if (Collision)
                    {   Error();
                    }
                    else 
                    {   Error();
                    }
                }
                else 
                {   Error();
                }
            }
        }
    }

    //seq2
    if (pressed2)
    {
        if (ms.TurnFront())
        {
            if (ms.TurnLeft())
            {
                Forward();
                delay(300);
                car.setRight(200);
                delay(300);
                Stop();
                Forward();
                delay(3000);
                Stop();
            }
            else 
            {
                Error();
            }
        }
        else 
        {
            Error();
        }
    }

    //seq3
    if (pressed3)
    {
        if (ms.TurnFront())
        {
            if (ms.TurnLeft())
            {
                if (ms.TurnRight())
                {
                    Forward();
                    delay(300);
                    car.setLeft(200);
                    delay(300);
                    Stop();
                    Forward();
                    delay(3000);
                    Stop();
                }
                else
                {
                    Error();
                }
            }
            else 
            {
                Error();
            }
        }
        else 
        {   
            Error();
        }
    }
}
