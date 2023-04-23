
#include "RearMotors.h"
#include "PwmOut.h"
#include "ThisThread.h"
#include "mbed.h"
#include <iostream>
#include <string>


#include "Servo.h"
#include "Car.h"


using namespace Car;

namespace RearMotors {
void initializeRearMotors() {

  std::cout << "Initializing rear escs... " << std::endl;

  leftMotor = 0.01;
  rightMotor = 0.01;

  // ledf = ledr = 1;
  ThisThread::sleep_for(500ms); // ESC detects signal
  // Required ESC Calibration/Arming sequence
  // sends longest and shortest PWM pulse to learn and arm at power on
  leftMotor = 0.99; // send longest PWM
  rightMotor = 0.99; // send longest PWM
  // ledf = ledr = 0;
  ThisThread::sleep_for(500ms);
  leftMotor = 0.47;
  rightMotor = 0.47;

//   for (float i = 0.45 ; i < 0.5; i += 0.01)
//     {
//         leftMotor = i;
//         rightMotor = i;
//         ThisThread::sleep_for(100ms);
//     }
  ThisThread::sleep_for(500ms);


  std::cout << "..Done\n";
}

// TODO: Map from -100 to +100 or from 0 to 100 but map it to only forward speed
// which is 0.46/0.47 to 1.0
void move(int speed) { // speed between 0 and 100
  // TODO: map from 50 to 90 or something for forward
  //       and from 46 to 10 (maybe) for backward

    
    float tmp = speed/100.0;
    float mappedMotorSpeed = 0.47+(1-0.47)*tmp;
  leftMotor = mappedMotorSpeed;
  rightMotor = mappedMotorSpeed;
}

void motorLoop(){
    move(10);

    while(1)
    {
        // do nothing for now
    }
}

} // namespace RearMotors