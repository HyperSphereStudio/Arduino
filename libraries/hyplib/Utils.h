//
// Created by JohnB on 11/21/2021.
//

#ifndef FINAL_PROJECT_UTILS_H
#define FINAL_PROJECT_UTILS_H

//Functions
template<typename T>
String str(T t){
    return String(t);
}

template<typename T>
static void print(T t){
    Serial.println(t);
}



#endif //FINAL_PROJECT_UTILS_H
