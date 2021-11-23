//
// Created by JohnB on 11/21/2021.
//

#ifndef FINAL_PROJECT_MAIN_H
#define FINAL_PROJECT_MAIN_H

#include "main.h"
#include "Robot.h"
#include "core.h"

void main_init(EventManager* mem){
    //Changing this may throw errors
    mem->subscribe(initEV, minit);
}

bool minit(int event, void* arg){
    //Put Initial Code here
    Control::setup();
    Robot::setup();
}


#endif //FINAL_PROJECT_MAIN_H
