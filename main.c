
#include <tm4c123gh6pm.h>

#define INPUT  0
#define OUTPUT 1

#define SOLENOID_1 PORTB_BIT1
#define SOLENOID_2 PORTB_BIT2
#define SOLENOID_3 PORTB_BIT3

void systick_delay(unsigned int);
void init_systick();

void main()
{
    DDRB_BIT1 = OUTPUT;
    DDRB_BIT2 = OUTPUT;
    DDRB_BIT3 = OUTPUT;

    const bool solenoid_1_pattern[] = {0, 0, 0, 0, 1, 1, 1, 1, ...};
    const bool solenoid_2_pattern[] = {0, 0, 1, 1, 0, 0, 1, 1, ...};
    const bool solenoid_3_pattern[] = {0, 1, 0, 1, 0, 1, 0, 1, ...};

    init_systick();

    float strumming_rate = 0.5;
    int i = 0;

    while (1)
    {
        SOLENOID_1 = solenoid_1_pattern[i];
        SOLENOID_2 = solenoid_2_pattern[i];
        SOLENOID_3 = solenoid_3_pattern[i];

        systick_delay(1000 / strumming_rate);
        i++;
    }
}

void systick_delay(unsigned long delay)
{
    unsigned long start_time = NVIC_ST_CURRENT_R;
    volatile unsigned long time_elapsed;

    do
    {
        time_elapsed = (start_time - NVIC_ST_CURRENT_R) & 0x00FFFFFF;
    }
    while(time_elapsed <= delay * 6000);
}

void init_systick()
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;
    NVIC_ST_CURRENT_R = 0;

    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE + NVIC_ST_CTRL_CLK_SRC;
}
