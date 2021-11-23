//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_CONTROL_H
#define FINAL_PROJECT_CONTROL_H
#include "lib.h"
#include "Configuration.h"
#include "EventManager.h"

#define Forward (-1)
#define Stop 0
#define Backward 1

#define RightMotor_EV 1
#define LeftMotor_EV 2
#define SWITCH_EV 3


class Control{
    public:
        static EventManager* cem;

        static void rightMotor(int motorSpeed);
        static void leftMotor(int motorSpeed);
        static float getDistance();
        static bool switchMode();
        static bool objectNearby();
        static void setup();
        static void driveMotors(Direction right, Direction left);
        static void free();
        static void update();
};

#endif //FINAL_PROJECT_CONTROL_H
