
#include "Servo.h"
#include "PwmOut.h"
#include "mbed.h"
#include <iostream>

mbed::PwmOut servo(D4);


namespace Servo{
 void initializeServo(){

    std::cout << "Initializing servos... ";
    servo.period(0.020f);
    std::cout << "..Done\n";
 }

 void steer(int angle){ //angle between 0 and 100

    float tmp = angle;
    tmp = tmp/100;

    servo.pulsewidth(0.001f + 0.001f * tmp);
 }

}
