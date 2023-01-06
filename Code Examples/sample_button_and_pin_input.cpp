/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdio>

// Blinking rate in milliseconds
#define UPDATES_MS     500ms

int main()
{
    printf("Hellow world!\n");
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED2);
    DigitalIn pin(PTB0);
    DigitalIn btn(SW2);

    while (true) {
        printf("BTN: %d PTA1: %d\n", pin.read(), btn.read());
        led.write(btn.read());
    }
}
