//
// Created by JohnB on 11/18/2021.
//

#include "Control.h"
#include "lib.h"

EventManager* Control::cem = nullptr;

void Control::setup(){
     cem = new EventManager();
     pinMode(trigPin, OUTPUT);
     pinMode(echoPin, INPUT);
     pinMode(switchPin, INPUT_PULLUP);

     pinMode(AIN1, OUTPUT);
     pinMode(AIN2, OUTPUT);
     pinMode(PWMA, OUTPUT);
     pinMode(BIN1, OUTPUT);
     pinMode(BIN2, OUTPUT);
     pinMode(PWMB, OUTPUT);

     print("Hello World!");
     print("Initializing...");
}

void Control::rightMotor(int motorSpeed)
{
    if (motorSpeed > 0)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }
    else if (motorSpeed < 0)
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
    }
    analogWrite(PWMA, abs(motorSpeed));

    str_fire(cem, RightMotor_EV, "Right Motor:" + str(motorSpeed));
}


void Control::leftMotor(int motorSpeed)
{
    if (motorSpeed > 0)
    {
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }
    else if (motorSpeed < 0)
    {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }
    else
    {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
    }
    analogWrite(PWMB, abs(motorSpeed));

    str_fire(cem, LeftMotor_EV, "Left Motor:" + str(motorSpeed));
}

float Control::getDistance()
{
    float echoTime;
    float calculatedDistance;

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    echoTime = pulseIn(echoPin, HIGH);
    calculatedDistance = echoTime / 148.0;
    return calculatedDistance;
}

bool Control::switchMode() {
    return digitalRead(switchPin) == LOW;
}


void Control::driveMotors(Direction rmotor, Direction lmotor){
        Control::rightMotor(rmotor * driveSpeed);
        Control::leftMotor(lmotor * driveSpeed);
}

bool Control::objectNearby() {
    return getDistance() <= close_distance;
}

void Control::free() {
    delete cem;
}

bool last_switch = false;
void Control::update() {
    bool new_switch = Control::switchMode();
    if(new_switch != last_switch)
        cem->fire(SWITCH_EV, new_switch);
    last_switch = new_switch;
}


