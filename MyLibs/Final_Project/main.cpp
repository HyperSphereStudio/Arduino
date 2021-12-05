/*--------------------------------
  Johnathan Bizzano 11/22/2021
  -----------------------------------------*/

#include "main.h"
#include "Robot.h"

EventFire minit;

void main_init(EventManager* mem){
    //Changing this may throw errors
    mem->subscribe(initEV, minit);
}

bool minit(int event, void* iteration) {
    //Put Initial Code here
    Control::setup();
    Robot::setup();
    yield();
}