#include "core.h"

EventManager* core::mem = new EventManager();

EventFire switch_change;

void core::init(int port, bool test){
    if(port != 0)
        Serial.begin(port);

    core::mem->fire(initEV, test);

    if(test){
        core::mem->fire(testEV, 0);
    }
}

long update_count = 0;
void core::loop(){
        core::mem->fire(updateEV, update_count);
        update_count++;
}

void core::destroy_main(){
    core::mem->fire(destroyEV, 0);
    delete core::mem;
}





