#include "Timer.h"

Timer::Timer() : lastUpdatedTime(0), stopTime(0), event(nullptr){}

Time Timer::timeLeft(){
    return millis() - lastUpdatedTime - stopTime;
}

void Timer::update(void* arg){
    if(isActive()){
        Time now = millis();
        if(timeLeft() <= 0 && event != nullptr){
            event(arg);
            lastUpdatedTime = 0;
        }
    }
}

void Timer::stop(){
    lastUpdatedTime = 0;
}

void Timer::reset(Time stopAt){
    start(stopAt, event);
}

void Timer::start(Time stopAt, TimeEvent* evnt){
    lastUpdatedTime = millis();
    event = evnt;
    stopTime = stopAt;
}

bool Timer::isActive(){
    return lastUpdatedTime != 0;
}
