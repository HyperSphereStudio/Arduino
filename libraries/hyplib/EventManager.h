/*--------------------------------
  Copywrite Johnathan Bizzano 11/22/2021
  Arduino Library

  Modification, Distribution and Decompilation are not allowed without written permission from Johnathan Bizzano
  -----------------------------------------*/

#ifndef HyperSphere_EventManager_H
#define HyperSphere_EventManager_H

#include "ArduinoSTL.h"
#include "map"

using namespace std;

namespace Hypersphere{
    typedef bool EventFire(int event, void* arg);

    class EventManager : public std::map<int, vector<void*>>{

        static bool _printer(int event, void* arg){
#if DEBUG
            Serial.println("Event:" + String(event) + "\tMessage:" + (char*) arg);
#endif
            return false;
        }

    public:
        EventManager() : std::map<int, vector<void*>>() {}
        ~EventManager() = default;

        void subscribe(int event){
            subscribe(event, _printer);
        }

        void subscribe(int event, EventFire ptr){
            if (!count(event)) {
                vector<void *> p;
                insert(pair<int, vector<void *>>(event, p));
            }
            operator[](event).push_back((void *) ptr);
        }

        void unsubscribe(int event, EventFire ptr){
            if (count(event)) {
                auto v = operator[](event);
                for(int i = 0; i < v.size();){
                    if(v[i] == ptr){
                        v.erase(v.begin() + i);
                    }else{
                        i++;
                    }
                }
                if(v.size() == 0)
                    erase(event);
            }
        }

        void fire(int event, String arg){
            fire<char*>(event, arg.begin());
        }

        void fire(int event, StringSumHelper arg){
            fire<char*>(event, arg.begin());
        }

        template<typename T>
        void fire(int event, T arg){
            if(count(event)){
                for (auto const& func : operator[](event)){
                    if(((EventFire*) func)(event, (void*) arg))
                        break;
                }
            }
        }

        int event_count(int event){
            if(count(event)){
                return operator[](event).size();
            }
            return 0;
        }
    };
}

#endif


