//
// Created by JohnB on 11/18/2021.
//

#include "Robot.h"


Robot *Robot::robot = nullptr;

Time Robot::turnTime = (Time) (1250.0 * 255.0) / driveSpeed;
Time Robot::driveTime = turnTime;

Robot::Robot() : lastUpdateTime(millis()), vol(0), angle(GNorth),
                 curr_loc(), robotState(PausedState),
                 wasCalibrated(false), states(this), object_graph(),
                 x(0), y(0), object_detection_delay(ObjectDetectionTimeThreshold) {
    change_state(ENABLE_CALIBRATION ? CalibratingState : MappingState, true, true);
    dprintstrl("Robot Initialized into State ");
    dprintln(robotState);
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
    double deltaTime = (millis() - lastUpdateTime) / 100.0;
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
            dprintstrlln("Detected Object");
            states[robotState]->object_detected(true);
        }else{
            dprintstrlln("Undetected Object");
            states[robotState]->object_detected(false);
        }
        delay(20);
    }
}


void Robot::free() {
    delete robot;
}

void Robot::driveForward() {
    dprintstrlln("Drive Forward");
    update();
    Control::right_motor.drive(driveSpeed);
    Control::left_motor.drive(driveSpeed);
    vol = 1;
}

void Robot::driveBackward() {
    dprintstrlln("Drive Backward");
    update();
    Control::right_motor.drive(-driveSpeed);
    Control::left_motor.drive(-driveSpeed);
    vol = -1;
}

void Robot::stop() {
    dprintstrlln("Robot Stop");
    update();
    Control::right_motor.drive(0);
    Control::left_motor.drive(0);
    vol = 0;
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
    dprintstrl("Turning Left. Facing:");
    dprintln(RobotGraph::dirstr(angle));
    update();
    Control::right_motor.drive(driveSpeed);
    Control::left_motor.drive(-driveSpeed);
    vol = 0;
    angle -= 1;
    angle = angle % 4 == 0 ? 0 : angle;
    delay(turnTime);
    stop();
}

void Robot::turnLeft() {
    dprintstrl("Turning Left. Facing:");
    dprintln(RobotGraph::dirstr(angle));
    update();
    Control::right_motor.drive(-driveSpeed);
    Control::left_motor.drive(driveSpeed);
    vol = 0;
    angle += 1;
    angle = angle % 4 == 0 ? 0 : angle;
    delay(turnTime);
    stop();
}

void Robot::turnAround() {
    dprintstrlln("Turning Around");
    turnRight();
    turnRight();
}

Robot::~Robot() {
    dprintstrlln("Destroying Robot");
    states.~RobotStates();
}

bool Robot::calibrated() const {
    return wasCalibrated;
}

void Robot::change_state(int next_state, bool fire_destroy, bool fire_init) {
    if (next_state != robotState) {
        dprintstrl("Changing State to:");
        dprint(next_state);
        dprintstrl(" Destroy:");
        dprint(fire_destroy);
        dprintstrl(" Init:");
        dprintln(fire_init);

        if (fire_destroy) {
            dprintstrl("Destroyed State ");
            dprintln(robotState);
            states[robotState]->destroy_state();
        }
        robotState = next_state;
        if (fire_init) {
            dprintstrl("Initialized State ");
            dprintln(robotState);
            states[robotState]->init_state();
        }
    }
}

void Robot::gotoPoint(RobotPoint p) {
    for(auto dir : object_graph.getPath(curr_loc, p)){
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
        }
    }
}

RobotPoint Robot::getForwardPoint(GraphType distance) const {
    switch(angle){
        case GEast:
            return {static_cast<GraphType>(distance + curr_loc.x), curr_loc.y};
        case GNorth:
            return {curr_loc.x, static_cast<GraphType>(distance + curr_loc.y)};
        case GSouth:
            return {curr_loc.x, static_cast<GraphType>(curr_loc.y - distance)};
        default:
            return {static_cast<GraphType>(curr_loc.x - distance), curr_loc.y};
    }
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
