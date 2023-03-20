
#include "RearMotors.h"
#include "PwmOut.h"
#include <iostream>
#include "mbed.h"

PwmOut pwm(D3);

namespace RearMotors{
 void initializeRearMotors(){
    pwm.period(0.00004f);
    pwm.write(38);
    std::cout << "Initializing rear escs... " << std::endl;
    wait_us(20000000);
    std::cout << "..Done\n";

 }

 void move(int speed){ //speed between 0 and 100

    //need to map!! 42 - 56
    float tmp = speed;
    tmp = tmp/100;
    pwm.write(tmp);
 }

}