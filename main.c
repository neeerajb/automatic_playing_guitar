#include <stdint.h>
#include <stdbool.h>
#include <tm4c123gh6pm.h>

// variables
unsigned long In;
unsigned long Out;
float strumming_rate = 2.3;

// functions
void systick_delay(unsigned long);
void init_systick();
void PortF_Init();
void chord_change(int chord[]);

// main code
void main()
{

    // Chord Pattern like C major, D major...
    int pattern_C[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0};
    int pattern_B[] = {0, 0, 1, 1, 1, 0, 1, 1, 0, 1};
    int pattern_R[] = {1, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    int pattern_G[] = {0, 1, 0, 1, 0, 1, 0, 1, 1, 1};

// Initialize SysTick with busy-wait running at bus clock:
    init_systick();

    float inc = 0.1;
    int i=-1;

    PortF_Init();

    while (1)
    {
        i++;
        if(i==0){                                   // Max value of i depends upon array of song
            chord_change(pattern_C);
        }
        if(i==1){                                   // Max value of i depends upon array of song
            chord_change(pattern_R);
        }
        if(i==2){                                   // Max value of i depends upon array of song
            chord_change(pattern_G);
        }
        if(i==3){                                   // Max value of i depends upon array of song
            chord_change(pattern_B);
            i=-1;
        }
        // Duration for which the same chord is played
        systick_delay(1000 * strumming_rate);
        systick_delay(1000 * strumming_rate);

        // Increase/Decrease the strumming time
        if(GPIO_PORTF_DATA_R & 0x10 == 0x10)        // checks if the switch 1 is pressed
        {
            strumming_rate += inc;

            if(strumming_rate > 2.5){               // 2.5 is achieved after testing. beyond that, the timer is at its limit
                strumming_rate = 0.5;                 // low strumming rate gives almost no time to play
            }
        }

        // Start or stop the chords
        if(GPIO_PORTF_DATA_R & 0x01 == 0x01){

            GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R & 0xF1;
            // add a delay after code starts or stop
            systick_delay(2000);                    // Around 2 seconds

            while(GPIO_PORTF_DATA_R & 0x01 == 0x01){
                // wait for the switch to be pressed
            }
        }


    }
}

void systick_delay(unsigned long delay)
{
    // Time delay using busy-wait.

    unsigned long start_time = NVIC_ST_CURRENT_R;
    volatile unsigned long time_elapsed;

    do
    {
        time_elapsed = (start_time - NVIC_ST_CURRENT_R) & 0x00FFFFFF;
    }
    while(time_elapsed <= delay * 6000);
}

void init_systick(void)
{
    // Initialize SysTick with busy-wait running at bus clock.

    NVIC_ST_CTRL_R = 0;                  // Disable SysTick during setup.
    NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M; // Maximum reload value.
    NVIC_ST_CURRENT_R = 0;               // Any write to current clears it.

    // Enable SysTick with core clock:
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE + NVIC_ST_CTRL_CLK_SRC;
}

void PortF_Init(void) {
    SYSCTL_RCGC2_R |= 0x00000020;           // activate clock for PortF
    while ((SYSCTL_PRGPIO_R & 0x00000020) == 0)
    {};                                     // wait until PortF is ready
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

    GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R & 0xE0;
    systick_delay(800);

    // step 2: check and turn individual pin
    if(chord[0] == 1){
        // switch the pin PF1 to 1
        In = GPIO_PORTF_DATA_R;             // change port as needed
        Out = In | 0x02;                    // PF1 set high
        GPIO_PORTF_DATA_R = Out;            // set the pin according to the pin variable

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
        // switch the pin PF2 to 1
        In = GPIO_PORTF_DATA_R;             // change port as needed
        Out = In | 0x04;                     // PF2 set high
        GPIO_PORTF_DATA_R = Out;            // set the pin according to the pin variable
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
        // switch the pin PF3 to 1
        In = GPIO_PORTF_DATA_R;             // change port as needed
        Out = In | 0x08;                     // PF3 set high
        GPIO_PORTF_DATA_R = Out;            // set the pin according to the pin variable
    }
    if(chord[9] == 1){
        // switch the pin to 1

    }



}
