#include "Cirk1A.h"

void exec(){
   pinMode(13, OUTPUT);
   MyLib::init();
   for(unsigned int i; i < 100; ++i){
        digitalWrite(13, HIGH);
        delay(2000);
        digitalWrite(13, LOW);
        delay(2000); 
    }
}