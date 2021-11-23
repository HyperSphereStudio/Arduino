//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_MAIN_H
#define FINAL_PROJECT_MAIN_H

#define initEV 0
#define updateEV 1
#define destroyEV 2
#define testEV 3

#include "EventManager.h"

class core{
public:
    static EventManager* mem;
};

void init_core(int port, bool test);
void main_loop();
void destroy_main();

#include "lib.h"

#endif //FINAL_PROJECT_MAIN_H
