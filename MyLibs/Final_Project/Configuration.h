//
// Created by JohnB on 11/18/2021.
//

#ifndef HyperSphere_Configuration_H
#define HyperSphere_Configuration_H

//Required
#define TEST false
#define SERIAL_PORT 9600
#define DEBUG true
#define Heart_Beat 1000

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

#define ObjectDetectionTimeThreshold 20
#define ObjectDetectionThreshold 10
#define ObjectDistanceSensorThreshold 10
#define CalibrationRotations 3
#define driveSpeed 255
#define ENABLE_CALIBRATION false
#define RobotWidth 15
#define RobotHeight 15

#include "core.h"




//Dont Change
#if DEBUG

#define dprintstrlln(string_literal) (debug_println(strl(string_literal)))
#define dprintln(v) (debug_println(v))
#define dprintstrl(string_literal) (debug_print(strl(string_literal)))
#define dprint(v) (debug_print(v))

#else

#define dprintstrlln(string_literal) ()
#define dprintln(v) ()
#define dprintstrl(string_literal) ()
#define dprint(v) ()

#endif



#endif