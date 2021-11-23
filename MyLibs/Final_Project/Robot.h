//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_ROBOT_H
#define FINAL_PROJECT_ROBOT_H

#include "Control.h"
#include "EventManager.h"


#define RobotForward_EV 1
#define RobotBackward_EV 2
#define RobotRightTurn_EV 3
#define RobotLeftTurn_EV 4
#define RobotStop_EV 5
#define RobotTurnAround_EV 6

class Robot : EventManager{
        Time lastUpdateTime;
        int vol;
        double angle;
        double robotX, robotY;


    public:
        static Robot* robot;

        EventManager* rem;

        Robot();
        ~Robot() = default;
        void update();
        float getX() const;
        float getY() const;

        void stop();
        void driveForward();
        void driveBackward();

        void stop(Time time);
        void driveForward(Time time);
        void driveBackward(Time time);

        void turnRight();
        void turnLeft();
        void turnAround();

        void calibrate();

        static void setup();
        static void free();
};


#endif //FINAL_PROJECT_ROBOT_H
