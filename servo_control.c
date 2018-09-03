#include <fsl_device_registers.h>
#include "utils.h"



//right servo instruction and control values
char instr_r = 's';
int ctrl_r;

//left servo instruction and control values
char instr_l = 's';
int ctrl_l;

int main (void)
{
	//char array for servo instructions
	char* instr = malloc(sizeof(char)*2);

	if (instr == NULL) {
		return -1;
	}

	//set up PWM and UART IO
	pwm_setup();
	uart_setup();
	
	while(1) {
		
		//Set ctrl for left motor
		if(instr_l == 'f'){ctrl_l = 300;}
		else if(instr_l == 'b' || instr_r == 'r'){ctrl_l = 200;}
		else ctrl_l = 250;
		
		//Set ctrl for right motor
		if(instr_r == 'f'){ctrl_r = 200;}
		else if(instr_r == 'b' || instr_r == 'r'){ctrl_r = 300;}
		else ctrl_r = 250;
		
		//Set motor PWM
		FTM0_C6V = ctrl_l;
		FTM3_C1V = ctrl_r;
		
		//Get new instructions
		get_instr(instr);
		instr_l = instr[0];
		instr_r = instr[1];
	}
}

//FTM Interupt Handlers
void FTM0_IRQHandler (void) {
	//Reset
	FTM0_SC &= ~(0x0080);
}

void FTM3_IRQHandler (void) {
	//Reset
	FTM3_SC &= ~(0x0080);
}