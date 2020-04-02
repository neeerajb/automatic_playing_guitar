
#include <tm4c123gh6pm.h>
#include <stdbool.h>

#define INPUT  0
#define OUTPUT 1

#define SOLENOID_1 PORTB_BIT1
#define SOLENOID_2 PORTB_BIT2
#define SOLENOID_3 PORTB_BIT3

void delay(unsigned int);

void main()
{
    DDRB_BIT1 = OUTPUT;
    DDRB_BIT2 = OUTPUT;
    DDRB_BIT3 = OUTPUT;

    const bool solenoid_1_pattern[] = {0, 0, 0, 0, 1, 1, 1, 1, ...};
    const bool solenoid_2_pattern[] = {0, 0, 1, 1, 0, 0, 1, 1, ...};
    const bool solenoid_3_pattern[] = {0, 1, 0, 1, 0, 1, 0, 1, ...};

    float strumming_rate = 0.5;
    int i = 0;

    while (true)
    {
        SOLENOID_1 = solenoid_1_pattern[i];
        SOLENOID_2 = solenoid_2_pattern[i];
        SOLENOID_3 = solenoid_3_pattern[i];

        delay(1000 / strumming_rate);
        i++;
    }
}

void delay(unsigned int num_millisecs)
{
    unsigned int millisec_ctr;
    unsigned int loop_ctr;

    for (millisec_ctr = 0; millisec_ctr < num_millisecs; millisec_ctr++)
    {
        for (loop_ctr = 0; loop_ctr < 331; loop_ctr++);
    }
}
