
#include <stdint.h>
#include <stdbool.h>
#include <tm4c123gh6pm.h>

#define INPUT  0
#define OUTPUT 1

void systick_delay(unsigned int);
void init_systick();
void PortF_Init();
void chord_change();


void main()
{

    // Chord Pattern like C major, D major...
    volatile int pattern_C[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0};
    volatile int solenoid_2_pattern[] = {0, 0, 1, 1, 0, 0, 1, 1, 1, 1};
    volatile int solenoid_3_pattern[] = {0, 1, 0, 1, 0, 1, 0, 1, 1, 1};

    init_systick();

    float strumming_rate = 0.5;

    PortF_Init();

    while (1)
    {
        // Turn on/off gpio pins
        chord_change(pattern_C);

        // Add delay for when the strumming should change using timer module
        // Use strumming_rate variable to change the time
        // something like systick_delay(1000 / strumming_rate);
        // for now
        while(i<400000){i++;}
        i=0;
        while(i<400000){i++;}
        i=0;
        while(i<400000){i++;}
        i=0;

    }
}

/*void systick_delay(unsigned long delay)
{
    unsigned long start_time = NVIC_ST_CURRENT_R;
    volatile unsigned long time_elapsed;

    do
    {
        time_elapsed = (start_time - NVIC_ST_CURRENT_R) & 0x00FFFFFF;
    }
    while(time_elapsed <= delay * 6000);
}*/

void init_systick()
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;
    NVIC_ST_CURRENT_R = 0;

    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE + NVIC_ST_CTRL_CLK_SRC;
}

void PortF_Init(void) {
    SYSCTL_RCGC2_R |= 0x00000020;           // activate clock for PortF
    while ((SYSCTL_PRGPIO_R & 0x00000020) == 0)
    {};                          // wait until PortF is ready
    GPIO_PORTF_LOCK_R = 0x4C4F434B;         // unlock GPIO PortF
    GPIO_PORTF_CR_R = 0x1F;                 // allow changes to PF4-0

    GPIO_PORTF_AMSEL_R = 0x00;              // disable analog on PortF
    GPIO_PORTF_PCTL_R = 0x00000000;         // use PF4-0 as GPIO
    GPIO_PORTF_DIR_R = 0x0E;                // PF4,PF0 in, PF3-1 out
    GPIO_PORTF_AFSEL_R = 0x00;              // disable alt function on PF
    GPIO_PORTF_PUR_R = 0x11;                // enable pull-up on PF0,PF4
    GPIO_PORTF_DEN_R = 0x1F;                // enable digital I/O on PF4-0
}

void chord_change(int chord[]){
    // step 1: turn all pins 0


    // step 2: check and turn individual pin
    if(chord[0] == 1){
        // switch the pin to 1

    }
    if(chord[1] == 1){
        // switch the pin to 1

    }
    if(chord[2] == 1){
        // switch the pin to 1

    }
    if(chord[3] == 1){
        // switch the pin to 1

    }
    if(chord[4] == 1){
        // switch the pin to 1

    }
    if(chord[5] == 1){
        // switch the pin to 1

    }
    if(chord[6] == 1){
        // switch the pin to 1

    }
    if(chord[7] == 1){
        // switch the pin to 1

    }
    if(chord[8] == 1){
        // switch the pin to 1

    }
    if(chord[9] == 1){
        // switch the pin to 1

    }



}
