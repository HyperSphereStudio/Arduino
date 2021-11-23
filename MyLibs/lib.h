#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Arduino.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/binary.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Client.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/IPAddress.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/new.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/PluggableUSB.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Print.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Printable.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Server.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Stream.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Udp.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/USBCore.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/USBDesc.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/WCharacter.h"
#include "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/WString.h"

extern HardwareSerial Serial;

class MyLib{
   public:
    static void init(){
        Serial.begin(9600);
    }
};
