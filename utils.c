#include <fsl_device_registers.h>

uint8_t get_char () {
	
	//Busy-wait until RDRF is set
	while (!(UART0_S1 & UART_S1_RDRF_MASK));
	
	//return char at head of FIFO queue
	return UART0_D;
}

void get_instr(char* instr) {
	//set instruction for left char
	instr[0] = get_char();
	//set instruction for right char
	instr[1] = get_char();
}


void pwm_setup(void) {
	//200, 250, 300 channel values for CC, S, C

	NVIC_EnableIRQ(FTM0_IRQn);  //Enable the FTM0 Interrupt
	NVIC_EnableIRQ(FTM3_IRQn); //Enable the FTM3 Interrupt

	//Enable FTM and Ports to clock gate
	
	SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK; 
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 
	
	SIM->SCGC3 |= SIM_SCGC3_FTM3_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; 
	
	PORTA_PCR1 = PORT_PCR_MUX(3); //Enable PTA1 to FTM0
	PORTD_PCR1 = PORT_PCR_MUX(4); //Enable PTD1 to FTM3
	
	//For Port A
	//Enabling timer overflow interupt, setting clock to system clock, prescale factor = 128
	FTM0->SC |= 0x004F; 
	//Setting PWM Frequency to 20 ms
	FTM0->MOD = 3280; 
	//Enabling edge-aligned PWM
	FTM0_C6SC |= 0x0028;
	//Setting Pulse-Width
	FTM0_C6V = 250; 
	
	//For Port D
	//Enabling timer overflow interupt, setting clock to system clock, prescale factor = 128
	FTM3->SC |= 0x004F;
	//Setting PWM Frequency to 20 ms
	FTM3->MOD = 3280;
	//Enabling edge-aligned PWM
	FTM3_C1SC |= 0x0028; 
	//Setting Pulse-Width
	FTM3_C1V = 250; 
}


void uart_setup(void) {
	
	//Enable UART and Ports to clock gate
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	
	
	PORTB_PCR16 |= PORT_PCR_MUX(3); //Enable PTB16 to UART0 RX
	
	
	UART0_C2 &= ~(UART_C2_RE_MASK ); //Disable RX
	UART0_C1 = 0; //Set to default value
	unsigned int baud = (uint16_t)((21000*1000)/(9600 * 16)); //baud rate calculation
	
	//Set High and Low BD registers
	unsigned int saved = UART0_BDH & ~(UART_BDH_SBR(0x1F));
	UART0_BDH = saved | (((baud & 0x1F00) >> 8));
	UART0_BDL = (uint8_t)(baud & UART_BDL_SBR_MASK);
	
	UART0_C2 |=(UART_C2_RE_MASK); //Enable RX
}

