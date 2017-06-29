#include "PSPMconfigure.h"
#include "PSPMport.h"
#include "mode.h"

static prv_tick_t INPUT;
static prv_tick_t OUTPUT;


void prv_time_trigger()
{
    if( prv_mode_is_period_end() == 1){  /* start a new mode, and trigger all the tasks in this mode*/
		prv_mode_switch();
	}

	if(prv_ef_is_time_to_trigger() == 1){
		prv_ef_triggering();
	}
}

void myHardwareInit(){
	init_led();
	init_rs232();
	enable_rs232_interrupts();
	enable_rs232();
}

void system_start()
{
    myHardwareInit();
    prv_ef_create();
	prv_mode_switch();
    port_scheduler_start();
}

void ps_duration_set_input(prv_tick_t t)
{
	INPUT = t;
}

void ps_duration_set_output(prv_tick_t t)
{
	OUTPUT = t;
}

prv_tick_t prv_duration_get_input()
{
	return INPUT;
}

prv_tick_t prv_duration_get_output()
{
	return OUTPUT;
}

void myTraceCreate      (){
}

void myTraceSwitchedIn  (){
}

void myTraceSwitchedOut	(){
}

void vApplicationTickHook( void )
{
	prv_time_trigger();
}

void vApplicationIdleHook()
{
}

//#define offsetof(s, m)   (char *)&(((s *)0)->m)
/**
 *get struct pointer from member pointer
 */

int gcd(int a, int b)
{
	return b == 0?a:gcd(b,a%b);
}

int lcm(int a, int b)
{
	return (a*b)/gcd(a,b);
}

// a simple itoa implementation

void itoa(int n , char *s)
{
	int i = 0;
	while(n){
		s[i++] = n%10 + '0';
		n /= 10;
	}
	s[i] = '\0';
}
