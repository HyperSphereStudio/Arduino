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
#include "EventManager.h"


#define initEV 0
#define updateEV 1
#define destroyEV 2
#define testEV 3

namespace Hypersphere{
    class core{
        public:
            static EventManager* mem;

            static void init(int port, bool test);
            static void destroy_main();
    };

    template<typename T>
    String str(T t){
        return String(t);
    }

    template<typename T>
    static void print(T t){
        Serial.println(t);
    }
}

using namespace Hypersphere;

#endif

