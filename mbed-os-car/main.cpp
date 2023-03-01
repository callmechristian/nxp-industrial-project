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

#include "pwm.h"
#include "linescan.h"



// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

int main()
{
    continousScan();
    // scan();
    // scan_2();
    // while(true)
    // {
    //     scan();
        
        
    //     ThisThread::sleep_for(BLINKING_RATE);
    // }
}
