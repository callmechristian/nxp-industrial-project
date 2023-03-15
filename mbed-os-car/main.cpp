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

#include "pwm.h"
#include "linescan.h"
#include "steering.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
Thread steeringThread;
#include "Servo.h"
#include "RearMotors.h"

using namespace Servo;
using namespace RearMotors;

using namespace Camera;
// using namespace M;
int main()
{
    // steeringThread.start(calculateSteer);
    

    // calculateSteer();
    std::cout << "heyla\n";
    initializeRearMotors();    
    initializeServo();
    // std::cout << "pizza\n";
    // move(42);
    // wait_us(4000000);
    // steer(60);
    // wait_us(4000000);
    // move(50);
    // std::cout << "hghghg\n";
    // wait_us(4000000);
    // steer(40);
    // wait_us(4000000);


    continousScan();
}
 