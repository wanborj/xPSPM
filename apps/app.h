#include "ef.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "stm32_p103.h"

void sensor1(void *);
void sensor2( void * );


void controller11(void *);
void controller12(void *);
void controller21(void *);
void controller22(void *);


void actuator1(void *);
void actuator2(void *);

bool mode_switch1();


