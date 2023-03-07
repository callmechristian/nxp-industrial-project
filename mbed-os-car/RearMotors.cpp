
#include "RearMotors.h"
#include "PwmOut.h"
#include <iostream>
#include "mbed.h"

PwmOut pwm(D3);

namespace RearMotors{
 void initializeRearMotors(){
    pwm.period(0.00004f);
    pwm.write(38);
    std::cout << "Initializing rear escs... ";
    wait_us(2000000);
    std::cout << "..Done\n";

 }

 void move(int speed){ //speed between 0 and 100

    //need to map!!
    float tmp = speed;
    tmp = tmp/100;
    pwm.write(tmp);
 }

}