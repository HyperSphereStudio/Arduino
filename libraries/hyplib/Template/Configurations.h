/*--------------------------------
  Johnathan Bizzano 11/22/2021
  -----------------------------------------*/

#ifndef HyperSphere_Configuration_H
#define HyperSphere_Configuration_H


//Required
#define TEST false
#define SERIAL_PORT 9600
#define DEBUG true

#include "core.h"



//Dont Change
#if DEBUG

#define dprintstrlln(string_literal) (debug_println(strl(string_literal)))
#define dprintln(v) (debug_println(v))
#define dprintstrl(string_literal) (debug_print(strl(string_literal)))
#define dprint(v) (debug_print(v))

#else

#define dprintstrlln(string_literal) ()
#define dprintln(v) ()
#define dprintstrl(string_literal) ()
#define dprint(v) ()

#endif

#endif