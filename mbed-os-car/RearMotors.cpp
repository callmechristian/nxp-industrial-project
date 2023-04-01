
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
    double wheel_l_speed = 0;
    double wheel_r_speed = 0;

void initializeRearMotors() {

  std::cout << "Initializing rear escs... " << std::endl;

  motor_r = 0.0;
  motor_l = 0.0;
  // ledf = ledr = 1;
  ThisThread::sleep_for(1s); // ESC detects signal
  // Required ESC Calibration/Arming sequence
  // sends longest and shortest PWM pulse to learn and arm at power on
  motor_r = 1.0; // send longest PWM
  motor_l = 1.0; // send longest PWM
  // ledf = ledr = 0;
  ThisThread::sleep_for(1s);
  motor_r = 0.46;
  motor_l = 0.46;
  ThisThread::sleep_for(1s);


  std::cout << "..Done\n";
}

// set left wheel speed with -1 being full speed backwards and 1 being full speed forward, 0 being no movement
void setLeftWheelSpeed(double speed) {
  if(speed >= 0) {
    motor_l = 0.46 + 0.54 * speed;
  } else {
    motor_l = 0.46 + 0.46 * speed;
  }
}

// set right wheel speed with -1 being full speed backwards and 1 being full speed forward, 0 being no movement
void setRightWheelSpeed(double speed) {
  if(speed >= 0) {
    motor_r = 0.46 + 0.54 * speed;
  } else {
    motor_r = 0.46 + 0.46 * speed;
  }
}

// from -1 to 1, with 0 being no wheel speed
void move(double speed) { // speed between -1 and 1
  setLeftWheelSpeed(speed);
  setRightWheelSpeed(speed);
}

void motorLoop(){
    // init as no speed
    move(0);

    // continous update
    while(1)
    {
        // set speed to pointer values
        setLeftWheelSpeed(wheel_l_speed);
        setRightWheelSpeed(wheel_r_speed);
    }
}

} // namespace RearMotors