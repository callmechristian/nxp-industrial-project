
#include "Own_Servo.h"
#include "PwmOut.h"
#include "mbed.h"
#include <iostream>

mbed::PwmOut servo(D3);


namespace Own_Servo{
 void initializeServo(){

    std::cout << "Initializing servos... ";
    servo.period(0.020f);
    std::cout << "..Done\n";
 }

 void steer(int angle){ //angle between 0 and 100

    float tmp = angle;
    // float tmp = 80;
    tmp = tmp/100;

    
    servo.pulsewidth(0.001f + 0.001f * tmp);
 }

}
