//
// Created by JohnB on 11/18/2021.
//

#include "Robot.h"


Robot *Robot::robot = nullptr;

Time Robot::turnTime = (Time) (500.0 * 255.0) / driveSpeed;
Time Robot::driveTime = 1000;

EventFire robot_heart_beat;

Robot::Robot() : lastUpdateTime(millis()), vol(0), angle(GNorth),
                 curr_loc(), robotState(PausedState),
                 wasCalibrated(false), states(this), object_graph(),
                 x(0), y(0), object_detection_delay(ObjectDetectionTimeThreshold), lastRobotState(0) {
    change_state(ENABLE_CALIBRATION ? CalibratingState : MappingState, true, true);

#if DEBUG
    dprintstrl("Robot Initialized into State ");
    dprintln(robotState);
    core::mem->subscribe(HeartbeatEV, robot_heart_beat);
    dprintstrlln("Control Initialization Called!");
#endif

    object_graph.setMinX(-MaxSpiralCount);
    object_graph.setMinY(-MaxSpiralCount);
    object_graph.setMaxX(MaxSpiralCount);
    object_graph.setMaxY(MaxSpiralCount);
}

void Robot::_update() {
    update();
    object_detection_check();
    if (!Control::swt.isActive() && robotState != PausedState) {
        change_state(PausedState, true, true);
    }
    Robot::robot->states[robotState]->update();
}

void Robot::update() {
    double deltaTime = ((double) millis() - lastUpdateTime) / driveTime;
    x += (vol * RobotGraph::dircos(angle) * deltaTime);
    y += (vol * RobotGraph::dirsin(angle) * deltaTime);
    curr_loc.x = x;
    curr_loc.y = y;
    lastUpdateTime = millis();
}

bool robot_update(int event, void *arg) {
    Robot::robot->_update();
    return false;
}

void Robot::setup() {
    dprintstrlln("Robot Initialization Called!");
    robot = new Robot();
    core::mem->subscribe(updateEV, robot_update);
}

void Robot::object_detection_check() {
    bool nearby = Control::objectNearby();
    if(object_detection_delay.update(nearby)){
        if (nearby) {
            dprintstrlln("ROBOT:Detected Object");
            states[robotState]->object_detected(true);
        }else{
            dprintstrlln("ROBOT:Undetected Object");
            states[robotState]->object_detected(false);
        }
        delay(20);
    }
}


void Robot::free() {
    delete robot;
}

void Robot::driveForward() {
    dprintstrlln("ROBOT:Drive Forward");
    update();
    Control::right_motor.drive(rightDriveSpeed);
    Control::left_motor.drive(leftDriveSpeed);
    vol = 1;
}

void Robot::driveBackward() {
    dprintstrlln("ROBOT:Drive Backward");
    update();
    Control::right_motor.drive(-rightDriveSpeed);
    Control::left_motor.drive(-leftDriveSpeed);
    vol = -1;
}



void Robot::stop() {
    dprintstrlln("ROBOT:Stop");
    _stop();
}

void Robot::driveForward(Time time) {
    driveForward();
    delay(time);
    stop();
}

void Robot::driveBackward(Time time) {
    driveBackward();
    delay(time);
    stop();
}

void Robot::stop(Time time) {
    stop();
    delay(time);
}

void Robot::turnRight() {
    angle = angle == 0 ? 3 : angle - 1;
    dprintstrl("ROBOT:Turning Right. Facing:");
    dprintln(RobotGraph::dirstr(angle));
    _stop();
    Control::right_motor.drive(turnSpeed);
    Control::left_motor.drive(-turnSpeed);
    vol = 0;
    delay(turnTime);
    object_detection_delay.reset();
    _stop();
}

void Robot::turnLeft() {
    angle = angle == 3 ? 0 : angle + 1;
    dprintstrl("ROBOT:Turning Left. Facing:");
    dprintln(RobotGraph::dirstr(angle));
    _stop();
    Control::right_motor.drive(-turnSpeed);
    Control::left_motor.drive(turnSpeed);
    vol = 0;
    delay(turnTime);
    object_detection_delay.reset();
    _stop();
}

void Robot::turnAround() {
    dprintstrlln("ROBOT:Turning Around");
    turnRight();
    turnRight();
}

Robot::~Robot() {
    dprintstrlln("ROBOT:Destroyed");
    states.~RobotStates();
}

bool Robot::calibrated() const {
    return wasCalibrated;
}

void Robot::change_state(int next_state, bool fire_destroy, bool fire_init) {
    lastRobotState = robotState;
    if (next_state != robotState) {
        dprintstrlln("=========State Change=========");
        dprintstrl("\tChanging State to:");
        dprint(states[next_state]->getName());
        dprintstrl("(");
        dprint(next_state);
        dprintstrl(")\tFrom State:");
        dprintln(states[robotState]->getName());
        dprintstrl("(");
        dprint(robotState);
        dprintstrl(")");

        if (fire_destroy) {
            dprintstrl("\tDestroying State ");
            states[robotState]->destroy_state();
            dprintln(states[robotState]->getName());
        }

        robotState = next_state;

        if (fire_init) {
            dprintstrl("\tInitializing State ");
            states[robotState]->init_state();
            dprintln(states[robotState]->getName());
        }

        dprintstrlln("================");
    }
}

void Robot::gotoPoint(RobotPoint p) {
    vector<GraphDirection> dirs;
    object_graph.getPath(curr_loc, p, &dirs);
    dprintstrl("Found Path!: Num Points:");
    dprintln(dirs.size());
    for(auto dir : dirs){
        switch(dir){
            case GEast:
                turnRight();
                driveForward(driveTime);
                break;
            case GWest:
                turnLeft();
                driveForward(driveTime);
                break;
            case GNorth:
                driveForward(driveTime);
                break;
            case GSouth:
                turnAround();
                driveForward(driveTime);
                break;
            case GEnd:
                dprintstrlln("Reached Location");
                break;
        }
    }
}

RobotPoint Robot::getForwardPoint(GraphType distance) const {
   return RobotPoint::getChangePoint(curr_loc, angle, distance);
}

bool Robot::isMoving() const {
    return vol != 0;
}

void Robot::resetPosition() {
    x = 0;
    y = 0;
    curr_loc.x = 0;
    curr_loc.y = 0;
    angle = GNorth;
}

GraphDirection Robot::getAngle() const {
    return angle;
}

int Robot::getVol() {
    return vol;
}

void Robot::_stop() {
    update();
    Control::right_motor.drive(0);
    Control::left_motor.drive(0);
    vol = 0;
    delay(500);
}

int Robot::getLastState() {
    return lastRobotState;
}

bool robot_heart_beat(int event, void* addr){
#if DEBUG
    if(Robot::robot != nullptr){
        dprintstrl("\tRobot Position ");
        print(Robot::robot->curr_loc);
        dprintstrl("\tVelocity:");
        dprint(Robot::robot->getVol());
        dprintstrl("\tDirection:");
        dprintln(RobotGraph::dirstr(Robot::robot->getAngle()));
    }
#endif
}