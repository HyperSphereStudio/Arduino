//
// Created by JohnB on 11/23/2021.
//

#ifndef FINAL_PROJECT_SWITCH_H
#define FINAL_PROJECT_SWITCH_H

#include "core.h"
#include "Instrument.h"

#define SwitchChange 0

class Switch : public Instrument{
    bool switch_state;
    bool last_state;
    int pin;
    EventManager em;
public:
    Switch(int pin);

    void init() override;
    void update() override;
    bool isActive();
};


#endif //FINAL_PROJECT_SWITCH_H
