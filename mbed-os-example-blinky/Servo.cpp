#include "mbed.h"
#include <iostream>

PwmOut servo(D3);

#define BLINKING_RATE     500ms

int servoo() {
    // servo requires a 20ms period    
    servo.period(0.020f);
    char str1[2];

    while(true)
    {

        scanf("%2s",str1);
        printf("atoi: %d", atoi(str1));
        float tmp = atoi(str1);
        tmp = tmp/100;
        std::cout << tmp << "\n";

        servo.pulsewidth(0.001f + 0.001f * tmp);
    }
}
