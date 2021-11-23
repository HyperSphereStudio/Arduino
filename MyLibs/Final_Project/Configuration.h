//
// Created by JohnB on 11/18/2021.
//

#ifndef HyperSphere_Configuration_H
#define HyperSphere_Configuration_H

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
#define CalibrationRotations 3
#define driveSpeed 255


#include "core.h"

#endif