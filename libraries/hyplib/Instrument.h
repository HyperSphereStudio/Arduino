//
// Created by JohnB on 11/23/2021.
//

#ifndef FINAL_PROJECT_INSTRUMENT_H
#define FINAL_PROJECT_INSTRUMENT_H

class Instrument{
public:
    EventManager em;

    Instrument() : em() {}

    virtual void init() = 0;
    virtual void update() = 0;
};

#endif //FINAL_PROJECT_INSTRUMENT_H
