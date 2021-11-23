#include <stdio.h>

#include "lib.h"
#include "Configuration.h"
#include "core.h"
#include "main.h"

void setup() {
    main_init(core::mem);
    init_core(SERIAL_PORT, TEST);
}

void loop(){}


