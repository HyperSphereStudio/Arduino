//
// Created by JohnB on 11/18/2021.
//

#include "Robot.h"

Robot* Robot::robot = nullptr;

Time turnTime = (Time) ((1250.0 * 255.0) / driveSpeed);
float robotDepth = 10, robotHeight = 10;

Robot::Robot() : lastUpdateTime(millis()), vol(0), angle(90),
        curr_loc(0, 0), object_distance_timer(), robotState(PausedState),
        wasCalibrated(false), object_graph(robotDepth, robotHeight){
    robotStates[PausedState] = new PausedRobotState(this);
    robotStates[CalibratingState] = new CalibratingRobotState(this);
    robotStates[MappingState] = new MappingRobotState(this);
    robotStates[DrivingState] = new DrivingRobotState(this);
}

void Robot::update(){
    updateStats();
    object_detection_check();
    if(Control::swt.isActive()){
        robotStates[robotState]->update();
    }else if(robotState != PausedState){
        change_state(PausedState);
    }
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
    r->robotStates[r->robotState]->object_detected(true);
}

void Robot::object_detection_check(){
    bool nearby = Control::objectNearby();
    object_distance_timer.update(this);
    if(object_distance_timer.isActive()){
        if(!nearby){
            object_distance_timer.stop();
            robotStates[robotState]->object_detected(false);
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
    for(auto & robotState : robotStates){
        delete robotState;
    }
}

bool Robot::calibrated() const {
    return wasCalibrated;
}

void Robot::change_state(int next_state) {
    if(next_state != robotState){
        robotStates[robotState]->destroy_state();
        robotState = next_state;
        robotStates[robotState]->init_state();
    }
}

void PausedRobotState::update(){
    if(r->calibrated()){
        r->change_state(MappingState);
    }else{
        r->change_state(CalibratingState);
    }
}





void CalibratingRobotState::init_state() {
    print("Put near wall");
    print("Calibrating...");
    Control::right_motor.drive(driveSpeed);
    Control::left_motor.drive(driveSpeed);
    start_time = millis();
    rotation_count = 0;
}

void CalibratingRobotState::update() {}

void CalibratingRobotState::destroy_state() {
    Control::right_motor.drive(0);
    Control::left_motor.drive(0);
}

void CalibratingRobotState::object_detected(bool mode){
    if(mode){
        if(rotation_count++ == CalibrationRotations){
            turnTime = (millis() - start_time) / (CalibrationRotations * 4);
            r->change_state(MappingState);
        }else{
            delay(100);
        }
    }
}




void MappingRobotState::destroy_state() {
    Control::right_motor.drive(0);
    Control::left_motor.drive(0);

}

void MappingRobotState::init_state() {
    r->curr_loc.x = 0;
    r->curr_loc.y = 0;

}

void MappingRobotState::update() {

}






void DrivingRobotState::destroy_state() {
    Control::right_motor.drive(0);
    Control::left_motor.drive(0);
}
