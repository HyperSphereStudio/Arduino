//
// Created by JohnB on 11/18/2021.
//

#include "Control.h"

Switch Control::swt(switchPin);
BasicMotor Control::right_motor(AIN1, AIN2, PWMA);
BasicMotor Control::left_motor(BIN1, BIN2, PWMB);
DistanceSensor Control::distanceSensor(trigPin, echoPin);

EventFire control_update;

void Control::setup(){
     swt.init();
     right_motor.init();
     left_motor.init();
     distanceSensor.init();

     core::mem->subscribe(updateEV, control_update);
     print("Hello World!");
     print("Initializing...");
}

bool control_update(int event, void* arg) {
    Control::swt.update();
    Control::distanceSensor.update();
    return false;
}

bool Control::objectNearby() {
    return distanceSensor.getDistance() <= close_distance;
}

void Control::free() {

}


