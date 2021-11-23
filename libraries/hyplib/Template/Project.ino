#include <stdio.h>
#include "core.h"
#include "Configuration.h"
#include "main.h"


void setup() {
	MAIN_FUNCTION();
    init_core(SERIAL_PORT, TEST);
}

void loop(){
    main_loop();
}


