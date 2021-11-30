//
// Created by JohnB on 11/29/2021.
//

#include "RobotStates.h"

RobotStates::RobotStates(Robot* r) {
    this->at(PausedState) = new PausedRobotState(r);
    this->at(CalibratingState) = new CalibratingRobotState(r);
    this->at(MappingState) = new MappingRobotState(r);
    this->at(DrivingState) = new DrivingRobotState(r);
    this->at(FailedMappingState) = new FailedMappingRobotState(r);
}

RobotStates::~RobotStates() {
    auto iter = begin();
    while(iter != end()){
        delete *iter;
    }
}


void PausedRobotState::update(){
    if(r->calibrated() || !ENABLE_CALIBRATION){
        r->change_state(MappingState, true, true);
    }else{
        r->change_state(CalibratingState, true, true);
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

void CalibratingRobotState::destroy_state() {
    r->stop();
}

void CalibratingRobotState::object_detected(bool mode){
    if(mode){
        if(rotation_count++ == CalibrationRotations){
            Robot::turnTime = (millis() - start_time) / (CalibrationRotations * 4);
            r->change_state(MappingState, true, true);
        }else{
            delay(50);
        }
    }
}


void MappingRobotState::destroy_state() {
    r->stop();
}

void MappingRobotState::init_state() {
    r->curr_loc.x = 0;
    r->curr_loc.y = 0;
    spiralDepth = 0;
    gotoLocation = r->curr_loc;
    print("Mapping State Started");
}

void MappingRobotState::update() {
    if(gotoLocation.distance(r->curr_loc) <= ObjectDetectionThreshold){
        gotoLocation = r->getForwardPoint(spiralDepth * RobotDepth);
        r->driveForward();
        spiralDepth++;
    }else if(!r->isMoving()){
        r->driveForward();
    }
}

void MappingRobotState::object_detected(bool mode) {
    if(mode){
        r->change_state(FailedMappingState, true, true);
    }
}


void DrivingRobotState::destroy_state() {
    r->stop();
}


void FailedMappingRobotState::init_state() {
    r->stop();
    gotoLocation = r->curr_loc;
    checkWallMode = false;
}

void FailedMappingRobotState::destroy_state() {
    r->stop();
}

void FailedMappingRobotState::object_detected(bool mode) {
    if(r->isMoving()){
        r->stop();
        r->turnLeft();
        checkWallMode = false;
    }
}

void FailedMappingRobotState::update() {
    if(gotoLocation.distance(r->curr_loc) <= ObjectDetectionThreshold) {
        if(checkWallMode) {
            r->turnLeft();
            r->change_state(MappingState, true, false);
        }else
            r->turnRight();
        checkWallMode = true;
        gotoLocation = r->getForwardPoint(RobotDepth);
    }else if(!r->isMoving()){
        r->driveForward();
    }
}
