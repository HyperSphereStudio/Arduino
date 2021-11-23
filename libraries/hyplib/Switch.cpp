//
// Created by JohnB on 11/23/2021.
//

#include "Switch.h"

Switch::Switch(int pin) : pin(pin), switch_state(false), Instrument(){}

bool Switch::isActive() {
    return switch_state;
}

void Switch::update() {
    switch_state = digitalRead(pin) == LOW;
    if(switch_state != last_state){
        em.fire(SwitchChange, switch_state);
    }
    last_state = switch_state;
}

void Switch::init() {
    pinMode(pin, INPUT_PULLUP);
}


