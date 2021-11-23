//
// Created by JohnB on 11/18/2021.
//

#include "Robot.h"

Robot* Robot::robot = nullptr;

Robot::Robot() : lastUpdateTime(millis()), vol(0), angle(90),
    robotX(0), robotY(0), rem(new EventManager()){}

void Robot::driveForward(){
    update();
    rem->fire(RobotForward_EV, 0);
    Control::driveMotors(Forward, Forward);
    vol = 1;
}

void Robot::driveBackward(){
    update();
    rem->fire(RobotBackward_EV, 0);
    Control::driveMotors(Backward, Backward);
    vol = -1;
}

void Robot::stop(){
    update();
    rem->fire(RobotStop_EV, 0);
    Control::driveMotors(Stop, Stop);
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
    rem->fire(RobotRightTurn_EV, 0);
    Control::driveMotors(Backward, Forward);
    vol = 0;
    angle -= 90;
    delay(turnTime);
    stop();
}

void Robot::turnLeft() {
    update();
    rem->fire(RobotLeftTurn_EV, 0);
    Control::driveMotors(Forward, Backward);
    vol = 0;
    angle += 90;
    delay(turnTime);
    stop();
}

void Robot::turnAround() {
    rem->fire(RobotTurnAround_EV, 0);
    turnRight();
    turnRight();
}

void Robot::update() {
    Time deltaTime = millis() - lastUpdateTime;
    robotX -= vol * cos(angle) * deltaTime;
    robotY -= vol * sin(angle) * deltaTime;
    lastUpdateTime = millis();
}

float Robot::getX() const {
    return robotX;
}

float Robot::getY() const{
    return robotY;
}

void Robot::calibrate() {
    long time_delay = 0;
    print("Put near wall");
    while(true){
        if(Control::objectNearby()){
            if(millis() - time_delay >= 5000){
                break;
            }else{
                time_delay = millis();
            }
        }
    }
    print("Calibrating...");
    delay(500);
}

void Robot::free() {
    delete robot;
}

void Robot::setup() {
    robot = new Robot();
}




