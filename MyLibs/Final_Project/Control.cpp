//
// Created by JohnB on 11/18/2021.
//

#include "Control.h"

Switch Control::swt(switchPin);
BasicMotor Control::right_motor(AIN1, AIN2, PWMA);
BasicMotor Control::left_motor(BIN1, BIN2, PWMB);
DistanceSensor Control::distanceSensor(trigPin, echoPin);

EventFire control_update;
EventFire heart_beat;

void Control::setup(){
     randomSeed(millis());
     swt.init();
     right_motor.init();
     left_motor.init();
     distanceSensor.init();

     core::mem->subscribe(updateEV, control_update);
#if DEBUG
     core::mem->subscribe(HeartbeatEV, heart_beat);
     dprintstrlln("Control Initialization Called!");
#endif
}

bool heart_beat(int event, void* iteration_addr){
#if DEBUG
    int usedDynamicRAM;
    int usedStaticRAM;
    int usedStackRAM;
    int freeRAM;
    core::raminfo(&usedDynamicRAM, &usedStaticRAM, &usedStackRAM, &freeRAM);
    dprintstrl("Heart Beat #");
    dprintln(deref<core_loop_update_addr_type>(iteration_addr));

    dprintstrl("RAM INFORMATION:  USED_DYN_RAM:");
    dprint(usedDynamicRAM);
    dprintstrl("\tUSED_STAT_RAM:");
    dprint(usedStaticRAM);
    dprintstrl("\tUSED_STAK_RAM:");
    dprint(usedStackRAM);
    dprintstrl("\tFREE_RAM:");
    dprintln(freeRAM);
#endif
    return false;
}

bool control_update(int event, void* iteration_addr) {
    Control::swt.update();
    Control::distanceSensor.update();
    return false;
}

bool Control::objectNearby() {
    return distanceSensor.getDistance() <= ObjectDistanceSensorThreshold;
}

void Control::free() {

}


