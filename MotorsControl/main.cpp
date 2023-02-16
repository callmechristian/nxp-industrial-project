/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "InterfaceDigitalOut.h"
#include "PinNames.h"
#include "PwmOut.h"
#include "mbed.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <iostream>


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


int main()
{
    // Initialise the digital pin LED1 as an output
    //DigitalOut led(LED1);
    char str1[2];
    PwmOut foo(D8);
    
    // foo.period(0.00004f);
    foo.period(0.01f);

    int i = 1;
    while(true)
    {

        scanf("%2s",str1);

        printf("atoi: %d\n", atoi(str1));

        float tmp = atoi(str1);
        tmp = tmp/100;

        foo.write(tmp);

        i++;
        if(i==100)
            i = 1;
        ThisThread::sleep_for(BLINKING_RATE);
    }    
}
