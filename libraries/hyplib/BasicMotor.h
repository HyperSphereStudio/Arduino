//
// Created by JohnB on 11/23/2021.
//

#ifndef FINAL_PROJECT_BASICMOTOR_H
#define FINAL_PROJECT_BASICMOTOR_H


class BasicMotor {
    int in1, in2, pw;
    bool opposite;
public:
    BasicMotor(int in1, int in2, int pw, bool opposite = false);

    void init();
    void drive(int motorSpeed);
};


#endif //FINAL_PROJECT_BASICMOTOR_H
