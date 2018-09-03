/*
utils.h file contains functions from utils.c for setting up and receiving serial 
and for setting up pwm. 
*/

//Gets 1 char from UART FIFO queue
uint8_t uart_getchar ();

//Setup UART0 and PTB16 for USB Serial
void uart_setup(void);

//Setup FTM0,FTM3,PTA1,PTD1 for PWM
void pwm_setup(void);

//Stores two chars from UART FIFO queue into instr
void get_instr(char* instr);