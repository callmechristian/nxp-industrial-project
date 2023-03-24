
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

  motor = 0.0;
  // ledf = ledr = 1;
  ThisThread::sleep_for(1s); // ESC detects signal
  // Required ESC Calibration/Arming sequence
  // sends longest and shortest PWM pulse to learn and arm at power on
  motor = 1.0; // send longest PWM
  // ledf = ledr = 0;
  ThisThread::sleep_for(1s);
  motor = 0.46;
  ThisThread::sleep_for(1s);


  std::cout << "..Done\n";
}

// TODO: Map from -100 to +100 or from 0 to 100 but map it to only forward speed
// which is 0.46/0.47 to 1.0
void move(int speed) { // speed between 0 and 100
  // TODO: map from 50 to 90 or something for forward
  //       and from 46 to 10 (maybe) for backward
  motor = speed / 100.;
}

void motorLoop(){
    move(52);

    while(1)
    {
        // do nothing for now
    }
}

} // namespace RearMotors