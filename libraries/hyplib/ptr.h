/*--------------------------------
  Copywrite Johnathan Bizzano 11/22/2021
  Arduino Library

  Modification, Distribution and Decompilation are not allowed without written permission from Johnathan Bizzano
  -----------------------------------------*/

#ifndef HyperSphere_ptr_H
#define HyperSphere_ptr_H

namespace Hypersphere {
    template<typename T>
    class ptr {
        T *_ptr;
    public:
        ptr<T>(T *t) : _ptr(t) {}

        ptr<T>() : _ptr(new T()) {}

        ~ptr() {
            delete _ptr;
        }

        T *operator->() {
            return _ptr;
        }

        T *get() {
            return _ptr;
        }
    };
}

#endif
