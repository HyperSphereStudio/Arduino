//
// Created by JohnB on 11/18/2021.
//

#include "Robot.h"


Robot* Robot::robot = nullptr;

Time Robot::turnTime = (Time) ((1250.0 * 255.0) / driveSpeed);


Robot::Robot() : lastUpdateTime(millis()), vol(0), angle(90),
        curr_loc(0, 0), object_distance_timer(), robotState(PausedState),
        wasCalibrated(false), states(this), object_graph(RobotDepth, RobotHeight){
    change_state(ENABLE_CALIBRATION ? CalibratingState : MappingState, true, true);
}

void Robot::update(){
    updateStats();
    object_detection_check();
    states[robotState]->update();
    /*if(!Control::swt.isActive() && robotState != PausedState){
        change_state(PausedState, true, true);
    }else{
        print("Test");

    }*/
}

void Robot::updateStats() {
    Time deltaTime = millis() - lastUpdateTime;
    curr_loc.x -= vol * cos(angle) * deltaTime;
    curr_loc.y -= vol * sin(angle) * deltaTime;
    lastUpdateTime = millis();
}

bool robot_update(int event, void* arg){
    Robot::robot->update();
    return false;
}

void Robot::setup() {
    robot = new Robot();
    core::mem->subscribe(updateEV, robot_update);
}


void Robot::object_was_detected(void* arg){
    auto r = ((Robot*) arg);
    r->states[r->robotState]->object_detected(true);
}

void Robot::object_detection_check(){
    bool nearby = Control::objectNearby();
    object_distance_timer.update(this);
    if(object_distance_timer.isActive()){
        if(!nearby){
            object_distance_timer.stop();
            states[robotState]->object_detected(false);
        }
    }else{
        if(nearby)
            object_distance_timer.start(ObjectDetectionThreshold, object_was_detected);
    }
}



void Robot::free() {
    delete robot;
}

void Robot::driveForward(){
    update();
    Control::right_motor.drive(driveSpeed);
    Control::left_motor.drive(driveSpeed);
    vol = 1;
}

void Robot::driveBackward(){
    update();
    Control::right_motor.drive(-driveSpeed);
    Control::left_motor.drive(-driveSpeed);
    vol = -1;
}

void Robot::stop(){
    update();
    Control::right_motor.drive(0);
    Control::left_motor.drive(0);
}

void Robot::driveForward(Time time){
    driveForward();
    delay(time);
    stop();
}

void Robot::driveBackward(Time time){
    driveBackward();
    delay(time);
    stop();
}

void Robot::stop(Time time){
    stop();
    delay(time);
}

void Robot::turnRight() {
    update();
    Control::right_motor.drive(driveSpeed);
    Control::left_motor.drive(-driveSpeed);
    vol = 0;
    angle -= PI / 2;
    delay(turnTime);
    stop();
}

void Robot::turnLeft() {
    update();
    Control::right_motor.drive(-driveSpeed);
    Control::left_motor.drive(driveSpeed);
    vol = 0;
    angle += PI / 2;
    delay(turnTime);
    stop();
}

void Robot::turnAround() {
    turnRight();
    turnRight();
}

Robot::~Robot() {
    states.~RobotStates();
}

bool Robot::calibrated() const {
    return wasCalibrated;
}

void Robot::change_state(int next_state, bool fire_destroy, bool fire_init) {
    if(next_state != robotState){
        if(fire_destroy)
            states[robotState]->destroy_state();
        robotState = next_state;
        if(fire_init)
            states[robotState]->init_state();
    }
}

void Robot::gotoPoint(Point<ustype> p) {

}

Point<ustype> Robot::getForwardPoint(ustype distance) const {
    if(angle == 0)
        return {static_cast<unsigned short>(distance + curr_loc.x), curr_loc.y};
    else if(angle == PI / 2)
        return {curr_loc.y, static_cast<unsigned short>(distance + curr_loc.y)};
    else if(angle == 3 * PI / 2)
        return {static_cast<unsigned short>(curr_loc.x - distance), curr_loc.y};
    else return {curr_loc.y, static_cast<unsigned short>(curr_loc.y - distance)};
}

bool Robot::isMoving() const{
    return vol == 0;
}
