//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_CONFIGURATION_H
#define FINAL_PROJECT_CONFIGURATION_H

#include "Utils.h"
#include "lib.h"

//Required
#define TEST false
#define SERIAL_PORT 9600
#define DEBUG true

#define STRPR true

//Pin Placements
#define switchPin 11
#define trigPin 10
#define echoPin 8

#define PWMA 3
#define AIN2 4
#define AIN1 5
#define BIN1 6
#define BIN2 7
#define PWMB 9

#define close_distance 15.0
#define ObjectDetectionThreshold 100
#define driveSpeed 255
static Time turnTime = (Time) ((1250.0 * 255.0) / driveSpeed);



#endif //FINAL_PROJECT_CONFIGURATION_H
