#ifndef FINAL_PROJECT_DISTANCESENSOR_H
#define FINAL_PROJECT_DISTANCESENSOR_H

#include "core.h"

class DistanceSensor{
    int trigger_pin;
    int echo_pin;
    float cached_distance;
public:
    DistanceSensor(int trigger_pin, int echo_pin);

    void init();
    void update();
    double getDistance();
};


#endif //FINAL_PROJECT_DISTANCESENSOR_H
