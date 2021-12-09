#include "core.h"

class EdgeDelay{
    Time delay;
    Time lastTime;
    bool state;
public:
    EdgeDelay(Time delay) : delay(delay){
        reset();
    }

    bool update(bool newState){
        if((state != newState) && (millis() - lastTime >= delay)){
            state = newState;
            lastTime = millis();
            return true;
        }else return false;
    }

    void reset(){
        state = false;
        lastTime = millis();
    }
};