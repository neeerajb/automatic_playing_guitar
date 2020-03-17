
#include "tm4c123gh6pm.h"
#include "GPIO.h"

unsigned long In;
unsigned long In2;
unsigned long Out;
void PortF_Init(void);
int i =0;
int sw1 = 0;

//unsigned long sw = GPIO_PORTF_DATA_R & 0x10;
/*
 * main.c
 */
int main(void) {
    PortF_Init();
    while(1){
        In = GPIO_PORTF_DATA_R & 0x10;      // read PF4 (SW1 state)
        if (In == 0x10) {
            sw1 = 1;
        }

    while (sw1 == 1) {
        //sw1 = sw1*-1;
        //In = GPIO_PORTF_DATA_R & 0x10;      // read PF4 (SW1 state)
        In2 = GPIO_PORTF_DATA_R & 0x01;     // read PF0 (SW2 state)


        In = In >> 3;                       // shift into PF2 position
        Out = GPIO_PORTF_DATA_R;
        Out = Out & 0xFB;                   // clear bit at PF2 position
        Out = Out | In;                     // set bit according to SW1
        GPIO_PORTF_DATA_R = Out;            // output
        while(i<800000){
            i++;
            Out = Out | In;
            GPIO_PORTF_DATA_R = Out;
            if(In2 != 0x01){
                Out = Out & 0xFD;
                In = In >> 1;
                Out = Out | In;
                GPIO_PORTF_DATA_R = Out;
                sw1 = 0;
                //while(In != 0x10){}
                //return;
            }

        }
        i=0;
        Out = Out & 0xF9;
        In = In << 1;
        Out = Out | In;
        GPIO_PORTF_DATA_R = Out;
        while(i<800000){
            i++;
            Out = Out | In;
            GPIO_PORTF_DATA_R = Out;
        }
        i=0;
        Out = Out & 0xF3;
        In = In << 1;
        Out = Out | In;
        GPIO_PORTF_DATA_R = Out;
        while(i<800000){
            i++;
            Out = Out | In;
            GPIO_PORTF_DATA_R = Out;
        }
        i=0;
        Out = Out & 0xF7;
        In = In << 1;
        Out = Out | In;
        GPIO_PORTF_DATA_R = Out;

        //while(In != 0x10){}

        //return;
    }
    }

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

