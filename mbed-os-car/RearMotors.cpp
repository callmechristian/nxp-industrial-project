
#include "RearMotors.h"
#include "PwmOut.h"
#include <iostream>
#include <string>
#include "ThisThread.h"
#include "mbed.h"

#include "Servo.h"

// PwmOut pwm(D4);

// namespace RearMotors{
//  void initializeRearMotors(){
//     pwm.period(0.00004f);
//     pwm.write(38);
//     std::cout << "Initializing rear escs... " << std::endl;
//     // ThisThread::sleep_for_us(10000000);
//     std::cout << "..Done\n";

//  }

//  void move(int speed){ //speed between 0 and 100

//     //need to map!! 42 - 56
//     float tmp = speed;
//     tmp = tmp/100;
//     pwm.write(tmp);
//  }

// }


Servo rear_motor(D4);

//PwmOut pwm(D3);

namespace RearMotors{
 void initializeRearMotors(){
    
    std::cout << "Initializing rear escs... " << std::endl;
    
    rear_motor = 0.0;
    // ledf = ledr = 1;
    ThisThread::sleep_for(500ms); //ESC detects signal
    //Required ESC Calibration/Arming sequence  
    //sends longest and shortest PWM pulse to learn and arm at power on
    rear_motor = 1.0; //send longest PWM
    // ledf = ledr = 0;

    rear_motor = 0.47;
    ThisThread::sleep_for(500ms);



    //ESC now operational using standard servo PWM signals
    // while (1) {
    //     for (float p=0.45; p<=0.6; p += 0.0125) { //Throttle up slowly to full throttle
    //         rear_motor = p;
    //         // ledf = p;
    //         std::cout << std::to_string(int(p*100)) << std::endl;
    //         std::cout << p << std::endl;

    //         ThisThread::sleep_for(1s);
    //     }
    //     // rear_motor = 0.0; //Motor off
    //     // ledf = ledr = 0;
    //     ThisThread::sleep_for(4s);
    //     for (float p=0.5; p>=0.38; p -= 0.0125) { //Throttle down slowly from full throttle
    //         rear_motor = p;
    //         std::cout << std::to_string(int(p*100)) << std::endl;
    //         // ledr = p;
    //         ThisThread::sleep_for(1s);
    //     }
    //     // rear_motor = 0.0; //Motor off
    //     // ledf = ledr = 0;
    //     ThisThread::sleep_for(4s);

    //     break;
    // }

    std::cout << "..Done\n";

 }

 void move(int speed){ //speed between 0 and 100
    // TODO: map from 50 to 90 or something for forward
    //       and from 46 to 10 (maybe) for backward
    rear_motor = speed/100.;
 }

}