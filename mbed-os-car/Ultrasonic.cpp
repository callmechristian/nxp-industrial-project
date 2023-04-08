/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "InterfaceDigitalOut.h"
#include "PinNames.h"

#include "mbed.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <iostream>

#include "Car.h"

using namespace Car;

namespace Ultrasonic
{
    int distance(){
        trig.write(0);
        wait_us(2);

        trig.write(1);
        wait_us(10);

        trig.write(0);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        int duration = 0;
        int distance = 0;

        Timer tmr;
        while (!echo){} // wait for high
        tmr.start();
        while (echo){} // wait for low
        duration = tmr.elapsed_time().count();

        // Calculating the distance
        distance = duration * 0.034 / 2;
        return distance;
    }
}
 