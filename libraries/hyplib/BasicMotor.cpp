//
// Created by JohnB on 11/23/2021.
//

#include "BasicMotor.h"
#include "core.h"

BasicMotor::BasicMotor(int IN1, int IN2, int PW, bool opposite = false) : in1(IN1), in2(IN2), pw(PW), opposite(opposite){}

void BasicMotor::init(){
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(pw, OUTPUT);
}

void BasicMotor::drive(int motorSpeed) {
    if(opposite){
        motorSpeed *= -1;
    }
    if (motorSpeed > 0)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    }
    else if (motorSpeed < 0)
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }
    else
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
    analogWrite(pw, abs(motorSpeed));
}
