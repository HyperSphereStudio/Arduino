//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_ROBOT_H
#define FINAL_PROJECT_ROBOT_H

#include "Control.h"
#include "Timer.h"
#include "Graph.h"


#define PausedState 0
#define CalibratingState 1
#define MappingState 2
#define DrivingState 3
#define NUM_ROBOT_STATES 4

class RobotState;
class MappingRobotState;

class Robot{
        friend MappingRobotState;

        Time lastUpdateTime;
        int vol;
        double angle;
        Point curr_loc;
        Timer object_distance_timer;
        RobotState* robotStates[NUM_ROBOT_STATES];
        int robotState;
        bool wasCalibrated;
        Graph object_graph;

        static void object_was_detected(void* arg);
        void object_detection_check();
        void updateStats();

    public:
        static Robot* robot;

        Robot();
        ~Robot();
        void update();

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
        void change_state(int next_state);

        static void setup();
        static void free();
};


class RobotState{
public:
    Robot* r;
    RobotState() : r(nullptr){}
    explicit RobotState(Robot* r) : r(r){}
    virtual void object_detected(bool mode){}
    virtual void update(){}
    virtual void init_state(){}
    virtual void destroy_state(){}
};

class PausedRobotState : public RobotState{
public:
    explicit PausedRobotState(Robot* r) : RobotState(r){}
    void update() override;
};

class CalibratingRobotState : public RobotState{
    int rotation_count;
    Time start_time;
public:
    explicit CalibratingRobotState(Robot* r) : RobotState(r), rotation_count(0){}
    void update() override;
    void init_state() override;
    void object_detected(bool mode) override;
    void destroy_state() override;
};

class MappingRobotState : public RobotState{
public:
    explicit MappingRobotState(Robot* r) : RobotState(r){}
    void init_state() override;
    void update() override;
    void destroy_state() override;
};

class DrivingRobotState : public RobotState{
public:
    explicit DrivingRobotState(Robot* r) : RobotState(r){}
    void destroy_state() override;
};


#endif //FINAL_PROJECT_ROBOT_H
