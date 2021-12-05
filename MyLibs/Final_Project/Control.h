//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_CONTROL_H
#define FINAL_PROJECT_CONTROL_H

#include "Configuration.h"
#include "Switch.h"
#include "BasicMotor.h"
#include "DistanceSensor.h"

class Control{
    public:
        static Switch swt;
        static BasicMotor right_motor;
        static BasicMotor left_motor;
        static DistanceSensor distanceSensor;

        static bool objectNearby();
        static void setup();
        static void free();
};

#endif //FINAL_PROJECT_CONTROL_H
