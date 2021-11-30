//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_ROBOT_H
#define FINAL_PROJECT_ROBOT_H

#include "Control.h"
#include "Timer.h"
#include "Graph.h"
#include "RobotStates.h"

class Robot{
        Time lastUpdateTime;
        int vol;
        double angle;
        Timer object_distance_timer;
        RobotStates states;
        int robotState;
        bool wasCalibrated;
        Graph<ustype> object_graph;

        static void object_was_detected(void* arg);
        void object_detection_check();
        void updateStats();

public:
        static Robot* robot;
        static Time turnTime;

        Point<ustype> curr_loc;

        Robot();
        ~Robot();
        void update();

        Point<ustype> getForwardPoint(ustype distance) const;
        void gotoPoint(Point<ustype> p);
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
        void change_state(int next_state, bool fire_destroy, bool fire_init);

        static void setup();
        static void free();
};


#endif //FINAL_PROJECT_ROBOT_H
