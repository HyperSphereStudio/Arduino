#include "core.h"

EventManager* core::mem = new EventManager();
int core::heart_beat = 0;

EventFire switch_change;

#define RAM_START ((char *) 0x20070000)

void core::init(int port, int ram_size, int beat, bool test){
    if(port != 0)
        Serial.begin(port);
    ramend = RAM_START + ram_size;
    heart_beat = beat;
    core::mem->fire(initEV, test);

    if(test){
        core::mem->fire(testEV, 0);
    }
}

core_loop_update_addr_type update_count = 0;
void core::loop(){
        core::mem->fire(updateEV, &update_count);
        if(update_count++ % heart_beat == 0){
            core_loop_update_addr_type count = (update_count - 1) / heart_beat;
            core::mem->fire(HeartbeatEV, &count);
        }
}

void core::destroy_main(){
    core::mem->fire(destroyEV, 0);
    delete core::mem;
}


char* core::ramend = 0;

void core::raminfo(int* usedDynamicRAM, int* usedStaticRAM, int* usedStackRAM, int* freeRAM){
    char *heapend = malloc(1);
    char stack_ptr = 0;

    usedStaticRAM[0] = &_end - RAM_START;
    usedStackRAM[0] = ramend - &stack_ptr;
    freeRAM[0] = &stack_ptr - heapend;
    free(heapend);
}

int core::rand_b(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}






