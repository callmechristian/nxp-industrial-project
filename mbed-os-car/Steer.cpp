#include "Steer.h"
#include <utility>
#include <vector>
#include "Camera.h"
#include <iostream>


#include "ThisThread.h"
#include "Car.h"
#include "Controller.h"
#include "RearMotors.h"

namespace Steer{
    double steeringAngle = 0.5; // assume steering is in neutral
    double prevSteeringAngle = 0.5; // assume initial position is neutral
    double prev_center = 64.0; // assume car is placed in the center of the track
    double angle_error_int = 0; // assume 0 initial condition for integrator
    double angle_error_prev = 0; // assume no angle error in initial condition
    double angle_output_prev = 0; // assume car started with no initial speed

    double STEER_BIAS = 0.1;

    // pointers to where we assign the motor speeds
    // double* wheel_l_speed_ptr = &RearMotors::wheel_l_speed;
    // double* wheel_r_speed_ptr = &RearMotors::wheel_r_speed;

    void initializeServo(){
        ThisThread::sleep_for(3s);

        std::cout<<"Calibrating Servo..."<<std::endl;
        Car::servo.calibrate();

        std::cout<<"Done."<<std::endl;

        // std::cout<<"Steering to 0.3"<<std::endl;
        Car::servo = 0.3+STEER_BIAS;
        ThisThread::sleep_for(1s);
        Car::servo = 0.7+STEER_BIAS;
        ThisThread::sleep_for(1s);
        std::cout<<"Steering back to half..."<<std::endl;
        Car::servo = 0.5+STEER_BIAS;
    }

    void calculateSteer(){

        int THRESHOLD = 50;
        int leftLine=0;
        int rightLine=128;
        int leftLine_consecutive = 0;
        int rightLine_consecutive = 0;
        int leftLine_consecutive_threshold = 1;
        int rightLine_consecutive_threshold = 1;

        std::vector<int> over;

        // find right line
        for (int i = 64; i < 128; i++)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                rightLine = i;
            //     rightLine_consecutive++;
            // } else {
            //     rightLine_consecutive = 0;
            // }
            // if (rightLine_consecutive >= rightLine_consecutive_threshold) {
            //     rightLine = i;
            //     break;
            // } else {
            //     rightLine = 128;
            }
        }

        // find left line
        for (int i = 64; i > 0; i--)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                leftLine = i;
            //     leftLine_consecutive++;
            // } else {
            //     leftLine_consecutive = 0;
            // }
            // if (rightLine_consecutive >= rightLine_consecutive_threshold) {
            //     leftLine = i;
            //     break;
            // } else {
            //     leftLine = 0;
            }
        }

        // compute center as the mean between the two pixel positions of the lines
        double center = (leftLine + rightLine) / 2.0;  

        // PD CONTROLLER for wheel angle
        // steeringAngle = Controller::angle_from_center_PD(center, prev_center, 0.01) + STEER_BIAS;

        // P CONTROLLER for wheel angle
        // steeringAngle = Controller::angle_from_center_P(center);
        steeringAngle = center/128.0;

        // PID CONTROLLER for individual wheel speed
        // std::pair<double, double> p = Controller::wheel_speed_controller_PID(steeringAngle, prevSteeringAngle, angle_error_int, angle_error_prev, angle_output_prev, Controller::sampling_time);
        // *wheel_l_speed_ptr = p.first;
        // *wheel_r_speed_ptr = p.second;
        // *wheel_l_speed_ptr = 0.1;
        // *wheel_r_speed_ptr = 0.1;

        

        // update previous center with current 
        prev_center = center;
        // update previous angle with current steering angle
        prevSteeringAngle = steeringAngle;

        // printf("%d\n", (int)(center));/
        
        // // uncomment for debug
        // std::string s = std::to_string(center)+"\t"+ std::to_string(steeringAngle)+"\n";
        // std::cout<< s<< std::endl;
    }

    void steerLoop(){
        while(1) {
            calculateSteer();
            // Car::servo = steeringAngle;
            Car::servo = steeringAngle;
            ThisThread::sleep_for(50ms); // WARNING!!! update sampling time in Controller.h accordingly!!!
        }
    }
}