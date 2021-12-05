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
        dprintstrlln("Control Initialization Called!");
}

bool control_update(int event, void* iteration_addr) {
    auto iteration = deref<core_loop_update_addr_type>(iteration_addr);

#if DEBUG
    if(iteration % HEARTBEAT == 0){
        int usedDynamicRAM;
        int usedStaticRAM;
        int usedStackRAM;
        int freeRAM;
        core::raminfo(&usedDynamicRAM, &usedStaticRAM, &usedStackRAM, &freeRAM);
        dprintstrl("Heart Beat #");
        dprintln(iteration);

        dprintstrl("RAM INFORMATION:  USED_DYN_RAM:");
        dprint(usedDynamicRAM);
        dprintstrl("\tUSED_STAT_RAM:");
        dprint(usedStaticRAM);
        dprintstrl("\tUSED_STAK_RAM:");
        dprint(usedStackRAM);
        dprintstrl("\tFREE_RAM:");
        dprintln(freeRAM);
    }
#endif

    Control::swt.update();
    Control::distanceSensor.update();
    return false;
}

bool Control::objectNearby() {
    return distanceSensor.getDistance() <= ObjectDistanceSensorThreshold;
}

void Control::free() {

}


