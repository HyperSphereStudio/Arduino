//
// Created by JohnB on 11/29/2021.
//

#ifndef FINAL_PROJECT_ROBOTSTATES_H
#define FINAL_PROJECT_ROBOTSTATES_H
#include "array"
#include "Graph.h"
#include "Configuration.h"

#define PausedState 0
#define CalibratingState 1
#define MappingState 2
#define DrivingState 3
#define FailedMappingState 4
#define NUM_ROBOT_STATES 5

typedef short GraphType;
typedef Point<GraphType, RobotWidth, RobotHeight> RobotPoint;
typedef Graph<GraphType, RobotWidth, RobotHeight> RobotGraph;

class Robot;

class RobotState{
public:
    Robot* r;
    RobotState() : r(nullptr){}
    virtual ~RobotState() = default;
    explicit RobotState(Robot* r) : r(r){}
    virtual void object_detected(bool mode){}
    virtual void update(){}
    virtual void init_state(){}
    virtual void destroy_state(){}
};

class RobotStates : public std::array<RobotState*, NUM_ROBOT_STATES>{
public:
    explicit RobotStates(Robot* r);
    ~RobotStates();
};


class PausedRobotState : public RobotState{
public:
    explicit PausedRobotState(Robot* r) : RobotState(r){}
    void update() override;
    void init_state() override;
};

class CalibratingRobotState : public RobotState{
    int rotation_count;
    Time start_time;
public:
    explicit CalibratingRobotState(Robot* r) : RobotState(r), rotation_count(0){}
    void init_state() override;
    void object_detected(bool mode) override;
    void destroy_state() override;
};

class MappingRobotState : public RobotState{
    GraphType spiralDepth;
public:
    RobotPoint gotoLocation;
    explicit MappingRobotState(Robot* r) : RobotState(r), gotoLocation(), spiralDepth(0){}
    void init_state() override;
    void update() override;
    void destroy_state() override;
    void object_detected(bool mode) override;
};

class FailedMappingRobotState : public RobotState{
    RobotPoint gotoLocation;
    RobotPoint mapLocation;
    bool checkWallMode;
    GraphDirection initDir;
    int num_failed_spirals;
public:
    explicit FailedMappingRobotState(Robot* r) : RobotState(r),
        gotoLocation(), checkWallMode(false), initDir(GNorth){}
    void init_state() override;
    void update() override;
    void destroy_state() override;
    void object_detected(bool mode) override;
};

class DrivingRobotState : public RobotState{
public:
    explicit DrivingRobotState(Robot* r) : RobotState(r){}
    void destroy_state() override;
    void update() override;
};


#include "Robot.h"
#endif //FINAL_PROJECT_ROBOTSTATES_H
