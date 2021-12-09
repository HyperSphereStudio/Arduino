

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
    r->stop();
}


void CalibratingRobotState::init_state() {
    Control::right_motor.drive(driveSpeed);
    Control::left_motor.drive(-driveSpeed);
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
    r->resetPosition();
    gotoPoint = r->curr_loc;
    spiralDepth = 1;
}

void MappingRobotState::update() {
    if(r->getLastState() == FailedMappingState){
        recalc_state();
        r->change_state(MappingState, false, false);
    }
    if(gotoPoint.compare(r->curr_loc)){
        if(spiralDepth == MaxSpiralCount){
            r->change_state(DrivingState, true, true);
        }else{
            r->turnLeft();
            recalc_state();
#if DEBUG
            dprintstrl("Spiral:");
            dprint(spiralDepth - 1);
            dprintstrl(". Goto:");
            print(gotoPoint);
            dprintstrl("\tFrom:");
            print(r->curr_loc);
            dprln;
#endif
        }
    }
}

void MappingRobotState::object_detected(bool mode) {
    if(mode){
        r->stop();
#if DEBUG
        dprintstrl("Plot Point:");
        print(r->curr_loc);
        dprln;
#endif
        r->object_graph.plotPoint(r->getForwardPoint(StepSize));
        r->change_state(FailedMappingState, true, true);
    }
}

void MappingRobotState::recalc_state() {
    gotoPoint = r->getForwardPoint(spiralDepth++ * StepSize);
    r->driveForward();
}


void DrivingRobotState::destroy_state() {
    r->stop();
}

void DrivingRobotState::update() {
    RobotPoint rp(core::rand_b(r->object_graph.getMinX(),r->object_graph.getMaxX()),
                    core::rand_b(r->object_graph.getMinY(),r->object_graph.getMaxY()));
    r->gotoPoint(rp);
    delay(5000);
}

void DrivingRobotState::init_state() {
    delay(5000);
}


void FailedMappingRobotState::init_state() {
    mappingPoint = r->getState<MappingRobotState>(MappingState).gotoPoint;
    initDir = r->getAngle();
    r->turnLeft();
    r->driveForward();
    gotoPoint = r->getForwardPoint(StepSize);
}

void FailedMappingRobotState::destroy_state() {
    r->stop();
}

void FailedMappingRobotState::object_detected(bool mode) {
    if(mode){
        r->stop();
        r->object_graph.plotPoint(r->getForwardPoint(StepSize));
        r->turnLeft();
        gotoPoint = r->getForwardPoint(StepSize);
        r->driveForward();

#if DEBUG
        dprintstrl("Plot Point:");
        print(r->curr_loc);
        dprln;
        dprintstrl("Goto:");
        print(gotoPoint);
        dprintstrl("\tFrom:");
        print(r->curr_loc);
        dprln;
#endif
    }
}

void FailedMappingRobotState::update() {
    if((initDir == r->getAngle() || RobotGraph::isLeft(initDir, r->getAngle())) && mappingPoint.comp_compare(r->curr_loc)){
        r->turnLeft();
        if(r->getAngle() == initDir){
            dprintln("Merging to current spiral");
            switch(r->getAngle()){
                case GWest:
                case GEast:
                    gotoPoint.y = r->curr_loc.y;
                    gotoPoint.x = mappingPoint.x;
                    break;
                case GNorth:
                case GSouth:
                    gotoPoint.y = mappingPoint.y;
                    gotoPoint.x = r->curr_loc.x;
                    break;
            }
            r->getState<MappingRobotState>(MappingState).gotoPoint = gotoPoint;
        }else{
            dprintln("Creating new Spiral");
        }
        r->change_state(MappingState, false, false);
        r->driveForward();
    }else if(gotoPoint.compare(r->curr_loc)) {
        if(initDir == r->getAngle() || RobotGraph::isRight(initDir, r->getAngle())){
            r->turnRight();
            gotoPoint = r->getForwardPoint(StepSize);
        }else{
            switch(r->getAngle()){
                case GWest:
                case GEast:
                    gotoPoint.y = mappingPoint.y;
                    gotoPoint.x = r->curr_loc.x;
                    break;
                case GNorth:
                case GSouth:
                    gotoPoint.y = r->curr_loc.y;
                    gotoPoint.x = mappingPoint.x;
                    break;
            }
        }
        r->driveForward();
#if DEBUG
        dprintstrl("Goto:");
        print(gotoPoint);
        dprintstrl("\tFrom:");
        print(r->curr_loc);
        dprln;
#endif
    }
}