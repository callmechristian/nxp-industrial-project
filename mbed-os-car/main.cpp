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
#include "steering.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
Thread steeringThread;

using namespace Camera;
// using namespace M;
int main()
{
    // steeringThread.start(calculateSteer);
    continousScan();

    // calculateSteer();
}
