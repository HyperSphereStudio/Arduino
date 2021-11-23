#include "main.h"

EventFire minit;

void main_init(EventManager* mem){
    //Changing this may throw errors
    mem->subscribe(initEV, minit);
}

bool minit(int event, void* arg){
    //Put Initial Code here
}
