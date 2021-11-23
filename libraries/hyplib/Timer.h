/*--------------------------------
  Copywrite Johnathan Bizzano 11/22/2021
  Arduino Library

  Modification, Distribution and Decompilation are not allowed without written permission from Johnathan Bizzano
  -----------------------------------------*/

#ifndef HyperSphere_Timer_H
#define HyperSphere_Timer_H

#include "core.h"

typedef void TimeEvent(void* arg);

namespace Hypersphere {
    class Timer {
        Time lastUpdatedTime, stopTime;
        TimeEvent* event;

    public:
        Timer();

        void update(void* arg);
        void stop();
        void reset(Time stopIn);
        void start(Time stopIn, TimeEvent event);
        Time timeLeft();
        bool isActive();
    };
}

#endif
