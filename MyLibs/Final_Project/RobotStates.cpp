

#include "RobotStates.h"

RobotStates::RobotStates(Robot* r) {
    this->at(PausedState) = new PausedRobotState(r);
    this->at(CalibratingState) = new CalibratingRobotState(r);
    this->at(MappingState) = new MappingRobotState(r);
    this->at(DrivingState) = new DrivingRobotState(r);
    this->at(FailedMappingState) = new FailedMappingRobotState(r);
}

RobotStates::~RobotStates() {
    dprintstrlln("Destroying Robot States");
    auto iter = begin();
    while(iter != end()){
        delete *iter;
    }
}


void PausedRobotState::update(){
    if(Control::swt.isActive()){
        dprintstrlln("Resuming Robot Activity");
        if(!ENABLE_CALIBRATION || r->calibrated()){
            r->change_state(MappingState, true, true);
        }else{
            r->change_state(CalibratingState, true, true);
        }
    } else if(r->isMoving()){
        r->stop();
    }
}

void PausedRobotState::init_state() {
    dprintstrlln("Paused Robot Activity");
    r->stop();
}


void CalibratingRobotState::init_state() {
    dprintstrlln("Put near wall");
    dprintstrlln("Calibrating...");
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
        dprintstrl("Calibration Rotation:");
        dprintln(rotation_count);
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
    dprintstrlln("Mapping State Started");
    r->resetPosition();
    gotoLocation = r->curr_loc;
    spiralDepth = 1;
}

void MappingRobotState::update() {
    if(gotoLocation.distance(r->curr_loc) <= ObjectDetectionThreshold){
#if DEBUG
        dprintstrl("Next Spiral:");
        dprint(spiralDepth);
        dprintstrl(". Goto:(");
        dprint(gotoLocation.x);
        dprintstrl(",");
        dprint(gotoLocation.y);
        dprintstrl(")\tFrom (");
        dprint(r->curr_loc.x);
        dprintstrl(",");
        dprint(r->curr_loc.y);
        dprintstrlln(")");
#endif

        r->turnLeft();
        r->driveForward();
        gotoLocation = r->getForwardPoint(spiralDepth++ * RobotHeight);
    }else if(!r->isMoving()){
        r->driveForward();
    }
}

void MappingRobotState::object_detected(bool mode) {
    if(mode){
#if DEBUG
        dprintstrl("Plot Point:(");
        dprint(r->curr_loc.x);
        dprintstrl(",");
        dprint(r->curr_loc.y);
        dprintstrlln(")");
#endif

        r->object_graph.plotPoint(r->curr_loc);
        r->change_state(FailedMappingState, false, false);
    }
}


void DrivingRobotState::destroy_state() {
    r->stop();
}

void DrivingRobotState::update() {
    RobotPoint rp(20, 20);
    r->gotoPoint(rp);
}


void FailedMappingRobotState::init_state() {
    dprintstrlln("Failed Mapping State Started");
    gotoLocation = r->curr_loc;
    mapLocation = r->getState<MappingRobotState>(MappingState).gotoLocation;
    initDir = r->getAngle();
    checkWallMode = false;
}

void FailedMappingRobotState::destroy_state() {
    r->stop();
}

bool nearEdge(RobotPoint mapLocation, GraphDirection initDir, Robot* r){
    switch(initDir){
        case GNorth:
        case GSouth:
            return abs(r->curr_loc.y - mapLocation.y) <= ObjectDetectionThreshold;
        default:
            return abs(r->curr_loc.x - mapLocation.x) <= ObjectDetectionThreshold;
    }
}

void FailedMappingRobotState::object_detected(bool mode) {
    if(mode && r->isMoving()){
#if DEBUG
        dprintstrl("Plot Point:(");
        dprint(r->curr_loc.x);
        dprintstrl(",");
        dprint(r->curr_loc.y);
        dprintstrlln(")");
#endif

        r->object_graph.plotPoint(r->curr_loc);
        if(checkWallMode){
            dprintstrlln("Turning away from wall");
            r->turnLeft();
            checkWallMode = false;
        }else{
            dprintstrlln("Spiral Truncation");
            r->turnLeft();
            if(nearEdge(mapLocation, initDir, r)){
                r->change_state(MappingState, true, false);
            }else{
                gotoLocation = r->getForwardPoint(RobotWidth);
                r->driveForward();
            }
        }
    }
}

void FailedMappingRobotState::update() {
    if(gotoLocation.distance(r->curr_loc) <= ObjectDetectionThreshold) {
        dprintstrlln("Reached Failed Goto Location");
        if(checkWallMode) {
            dprintstrlln("Checking Wall");
            r->turnRight();
            r->driveForward();
        }else{
            r->turnLeft();
            checkWallMode = true;
        }
        gotoLocation = r->getForwardPoint(RobotHeight);
    }else if(!r->isMoving()){
        dprintstrlln("Starting Failed Driving");
        r->driveForward();
    }
}
