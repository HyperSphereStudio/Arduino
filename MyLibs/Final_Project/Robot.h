//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_ROBOT_H
#define FINAL_PROJECT_ROBOT_H

#include "Control.h"
#include "Timer.h"
#include "Graph.h"
#include "RobotStates.h"
#include "EdgeDelay.h"

class Robot{
        Time lastUpdateTime;
        int vol;
        GraphDirection angle;
        double x, y;
        int robotState, lastRobotState;
        bool wasCalibrated;
        EdgeDelay object_detection_delay;

        void object_detection_check();
        void _stop();
public:
        static Robot* robot;
        static Time turnTime;
        static Time driveTime;

        RobotStates states;
        RobotPoint curr_loc;
        RobotGraph object_graph;

        Robot();
        ~Robot();

        void _update();
        void update();
        RobotPoint getForwardPoint(GraphType distance) const;
        void gotoPoint(RobotPoint p);
        void stop();
        void driveForward();
        void driveBackward();

        void stop(Time time);
        void driveForward(Time time);
        void driveBackward(Time time);

        void turnRight();
        void turnLeft();
        void turnAround();
        bool calibrated() const;
        bool isMoving() const;
        int getVol();
        int getLastState();
        void change_state(int next_state, bool fire_destroy, bool fire_init);
        void resetPosition();
        GraphDirection getAngle() const;

        template<typename T>
        T getState(int state){
            return *((T*) (states.begin() + state));
        }

        static void setup();
        static void free();
};


#endif //FINAL_PROJECT_ROBOT_H
