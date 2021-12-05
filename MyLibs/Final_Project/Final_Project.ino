/*--------------------------------
  Johnathan Bizzano 11/22/2021
  -----------------------------------------*/

#include <stdio.h>
#include "Configuration.h"
#include "main.h"

void setup() {
    main_init(core::mem);
    core::init(SERIAL_PORT, 32000, Heart_Beat, TEST);
}

void loop(){
    core::loop();
}


