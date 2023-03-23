/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

int PixelArray[128];
int i = 0;
uint32_t sensorSaturation = 0;

int main()
{
    // debug
    printf("Program started...\n");

    // set led for debugging operations
    DigitalOut led(LED1);

    // clk and si pins
    DigitalOut clk(D8); // pwm
    DigitalOut si(D7);

    // A0 analog in
    AnalogIn sensor_out(A0);

    // initialize camera
    si.write(1);
    clk.write(1);
    si.write(0);
    clk.write(0);

    // cycle through all pixels for first pass
    for(i = 0; i < 128; i ++){
        clk.write(1);
        clk.write(0);
    }

    // loop
    while(true) {
        sensorSaturation = sensor_out.read()*3.3f;   // Get value for saturation time.

        si.write(1);
        clk.write(1);
        si.write(0);
        clk.write(0);

        for(i = 0; i < 128; i ++){
            led.write(1);
            ThisThread::sleep_for((uint32_t)sensorSaturation);    //  saturation time
            PixelArray[i] = sensor_out.read()*255;
            clk.write(1);
            clk.write(0);
            led.write(0);
        }

        for(i = 0; i < 128; i ++){
            printf("%d",PixelArray[i]);
            if(i!=127){
                printf(",");
            }  
        }
        printf("\n");
    }
}
