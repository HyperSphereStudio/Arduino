//
// Created by JohnB on 11/21/2021.
//

#ifndef FINAL_PROJECT_PTR_H
#define FINAL_PROJECT_PTR_H

template<typename T>
class ptr{
    T* _ptr;
public:
    ptr<T>(T* t) : _ptr(t){}

    ptr<T>() : _ptr(new T()){}

    ~ptr(){
        delete _ptr;
    }

    T* operator->() {
        return _ptr;
    }

    T* get(){
        return _ptr;
    }
};

#endif //FINAL_PROJECT_PTR_H
