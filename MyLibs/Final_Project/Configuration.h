//
// Created by JohnB on 11/18/2021.
//

#ifndef HyperSphere_Configuration_H
#define HyperSphere_Configuration_H

//Required
#define TEST false
#define SERIAL_PORT 9600
#define DEBUG true
#define Heart_Beat 2000

//Pin Placements
#define switchPin 7
#define trigPin 6
#define echoPin 5

#define PWMA 11
#define AIN2 12
#define AIN1 13
#define BIN1 8
#define BIN2 9
#define PWMB 10

#define OppositeMotorDirection true
#define ObjectDetectionTimeThreshold 20
#define ObjectDistanceSensorThreshold 7
#define CalibrationRotations 3
#define driveSpeed 200
#define rightDriveSpeed 100
#define leftDriveSpeed 105
#define turnSpeed 140
#define ENABLE_CALIBRATION false
#define Version "2.0.4"
#define MaxSpiralCount 8
#define StepSize 1

#include "core.h"





//Dont Change
#if DEBUG

#define dprintstrlln(string_literal) (debug_println(strl(string_literal)))
#define dprintln(v) (debug_println(v))
#define dprintstrl(string_literal) (debug_print(strl(string_literal)))
#define dprint(v) (debug_print(v))
#define dprln (dprintstrl("\n"))

#else

#define dprintstrlln(string_literal) ()
#define dprintln(v) ()
#define dprintstrl(string_literal) ()
#define dprint(v) ()
#define dprln ()

#endif



#endif