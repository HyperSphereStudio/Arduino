cmake_minimum_required(VERSION 3.19)
project(Final_Project)

include_directories(../../libraries/scpp)
include_directories($ENV{ProgramFiles\(x86\)}/Arduino/hardware/arduino/avr/cores/arduino)
include_directories($ENV{ProgramFiles\(x86\)}/Arduino/libraries/LiquidCrystal/src)
include_directories(../../libraries/hyplib)

set(CMAKE_CXX_STANDARD 14)

add_library(Final_Project Control.cpp Control.h Configuration.h
        Graph.cpp Graph.h Robot.cpp Robot.h)