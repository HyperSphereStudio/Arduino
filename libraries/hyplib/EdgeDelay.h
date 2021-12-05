#include "core.h"

class EdgeDelay{
    Time delay;
    Time lastTime;
    bool state;
    bool first;
public:
    EdgeDelay(Time delay) : delay(delay){
        reset();
    }

    bool update(bool newState){
        if((state != newState || first) && (millis() - lastTime >= delay)){
            state = newState;
            lastTime = millis();
            first = false;
            return true;
        }else return false;
    }

    void reset(){
        state = false;
        first = true;
        lastTime = millis();
    }
};