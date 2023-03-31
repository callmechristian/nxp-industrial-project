#include "Steer.h"
#include <vector>
#include "Camera.h"
#include <iostream>


#include "ThisThread.h"
#include "Car.h"
// #include "Controller.h"

namespace Steer{
    double steeringAngle = 0.5; // assume steering is in neutral
    double prev_center = 64.0; // assume car is placed in the center of the track

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
        int rightLine=128;
        int leftLine_consecutive = 0;
        int rightLine_consecutive = 0;
        int leftLine_consecutive_threshold = 2;
        int rightLine_consecutive_threshold = 2;

        std::vector<int> over;

        // find right line
        for (int i = 64; i < 128; i++)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                rightLine = i;
                rightLine_consecutive++;
            } else {
                rightLine_consecutive = 0;
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
            } else {
                leftLine_consecutive = 0;
            }
            if (rightLine_consecutive >= rightLine_consecutive_threshold) {
                break;
            }
        }

        // compute center as the mean between the two pixel positions of the lines
        double center = (leftLine + rightLine) / 2.0;  

        // PD CONTROLLER
        double Kp = 0.2;
        double Kd = 0.1;
        steeringAngle = angle_from_center_PD(center, prev_center, Kp, Kd, 0.01);

        // update previous center with current 
        prev_center = center;
        
        // // uncomment for debug
        // std::string s = std::to_string(center)+"\t"+ std::to_string(steeringAngle)+"\n";
        // std::cout<< s<< std::endl;
    }

    void steerLoop(){
        while(1) {
            calculateSteer();
            Car::servo = steeringAngle;
            ThisThread::sleep_for(10ms);
        }
    }
}