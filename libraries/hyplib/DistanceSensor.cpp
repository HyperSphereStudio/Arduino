//
// Created by JohnB on 11/23/2021.
//

#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int trigPin, int echoPin) : trigger_pin(trigPin), echo_pin(echoPin){}

double DistanceSensor::getDistance() {
    return cached_distance;
}

void DistanceSensor::update() {
    float echoTime;
    float calculatedDistance;

    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);

    echoTime = pulseIn(echo_pin, HIGH);
    calculatedDistance = echoTime / 148.0;
    cached_distance = calculatedDistance;
}

void DistanceSensor::init() {
    pinMode(trigger_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
}
