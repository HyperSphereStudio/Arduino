#include "core.h"
#include "Utils.h"

EventManager* core::mem = new EventManager();

EventFire switch_change;

void init_core(int port, bool test){
    if(port != 0)
        Serial.begin(port);

    long update_count = 0;
    core::mem->fire(initEV, test);

    if(test){
        core::mem->fire(testEV, 0);
    }else{
        while(true){
            core::mem->fire(updateEV, update_count);
            update_count++;
        }
    }
}

void destroy_main(){
    core::mem->fire(destroyEV, 0);
    delete core::mem;
}





