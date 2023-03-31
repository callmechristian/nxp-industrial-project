#include "Steer.h"
#include <vector>
#include "Camera.h"
#include <iostream>


#include "ThisThread.h"
#include "Car.h"
// #include "Controller.h"

namespace Steer{
    double steeringAngle = 50.0;
    double prev_err = 0.0;
    double Kd = 0.1;
    double Kp = 3.0;

    void initializeServo(){
        ThisThread::sleep_for(3s);

        std::cout<<"Calibrating Servo..."<<std::endl;
        Car::servo.calibrate();

        std::cout<<"Done."<<std::endl;

        // std::cout<<"Steering to 0.3"<<std::endl;
        Car::servo = 0.3;
        ThisThread::sleep_for(1s);
        std::cout<<"Steering back to half..."<<std::endl;
        Car::servo = 0.5;
    }

    void calculateSteer(){

        int THRESHOLD = 50;
        int leftLine=0;
        int rightLine=0;
        int leftLine_consecutive = 0;
        int rightLine_consecutive = 0;
        int leftLine_consecutive_threshold = 2;
        int rightLine_consecutive_threshold = 2;

        std::vector<int> over;

        // TODO: for robustness, make sure at least 3 consecutive pixels are over the threshold?
        // find right line
        for (int i = 64; i < 128; i++)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                rightLine = i;
                rightLine_consecutive++;
            }
            if (rightLine_consecutive >= rightLine_consecutive_threshold) {
                break;
            }
        }

        // find left line
        for (int i = 64; i > 0; i--)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                leftLine = i;
                leftLine_consecutive++;
            }
            if (rightLine_consecutive >= rightLine_consecutive_threshold) {
                break;
            }
        }

        // set left line to max if it is not recognized
        if (leftLine == 0) {
            leftLine = 64;
        }

        // set right line to max if it is not recognized
        if (rightLine == 0) {
            rightLine = 64;
        }

        double center = (leftLine + rightLine) / 2.0;

        double displacement = (center - 64);

        double error_deriv = displacement - prev_err;

        // steeringAngle = 50 + Kp * displacement + Kd * error_deriv;
        steeringAngle = 50 + Kp * displacement;
        
        std::string s = std::to_string(center)+"\t"+ std::to_string(steeringAngle)+"\n";
        // std::cout<< s<< std::endl;
    }

    void steerLoop(){
        while(1) {
            calculateSteer();
            Car::servo = steeringAngle/100.;
            ThisThread::sleep_for(10ms);
        }
    }
}