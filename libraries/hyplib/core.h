/*--------------------------------
  Copywrite Johnathan Bizzano 11/22/2021
  Arduino Library

  Modification, Distribution and Decompilation are not allowed without written permission from Johnathan Bizzano
  -----------------------------------------*/


#ifndef HyperSphere_Core_H
#define HyperSphere_Core_H

#include "Arduino.h"
#include "binary.h"
#include "Client.h"
#include "HardwareSerial.h"
#include "IPAddress.h"
#include "new.h"
#include "PluggableUSB.h"
#include "Print.h"
#include "Printable.h"
#include "Server.h"
#include "Stream.h"
#include "Udp.h"
#include "USBCore.h"
#include "USBDesc.h"
#include "WCharacter.h"
#include "WString.h"
#include "ArduinoSTL.h"


extern HardwareSerial Serial;
typedef unsigned long Time;
typedef unsigned int Ptr;
typedef unsigned long core_loop_update_addr_type;

#include "EventManager.h"


#define initEV 0
#define updateEV 1
#define destroyEV 2
#define testEV 3
#define HeartbeatEV 4
#define ReservedEV_Count 5


#define CHECK_TYPE(var,type) { __typeof(var) *__tmp; __tmp = (type *)NULL; (void)__tmp; }
#define strl(str_literal) F(str_literal)

extern char _end;

namespace Hypersphere{
    class core{
        static char *ramend;
        static int heart_beat;
        public:
            static EventManager* mem;

            static int rand_b(int lower, int upper);
            static void init(int port, int ram_size, int heart_beat, bool test);
            static void destroy_main();
            static void loop();
            static void raminfo(int* usedDynamicRAM, int* usedStaticRAM, int* usedStackRAM, int* freeRAM);
            static void printraminfo();
    };

    template<typename T>
    inline T deref(void* addr){
        return *((T*) addr);
    }

    template<typename T>
    String str(T t){
        return String(t);
    }

    template<typename T>
    constexpr void debug_println(T t){
            Serial.println(t);
            Serial.flush();
    }

    template<typename T>
    constexpr void debug_print(T t){
        Serial.print(t);
        Serial.flush();
    }
}

using namespace Hypersphere;

#endif

