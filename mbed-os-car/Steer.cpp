#include "Steer.h"
#include <vector>
#include "Camera.h"
#include <iostream>


#include "ThisThread.h"
#include "Car.h"
// #include "Controller.h"

namespace Steer{
    int steeringAngle = 50;

    void initializeServo(){
        ThisThread::sleep_for(3s);

        std::cout<<"Calibrating Servo..."<<std::endl;
        Car::servo.calibrate();

        std::cout<<"Done."<<std::endl;

        // std::cout<<"Steering to 0.3"<<std::endl;
        // Car::servo = 0.3;
    }

    void calculateSteer(){

        int THRESHOLD = 50;
        int leftLine=0;
        int rightLine=0;
        std::vector<int> over;

        // TODO: for robustness, make sure at least 3 consecutive pixels are over the threshold?
        // find right line
        for (int i = 64; i < 128; i++)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                rightLine = i;
                break;
            }
        }

        // find left line
        for (int i = 64; i > 0; i--)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                leftLine = i;
                break;
            }
        }

        int center = (leftLine + rightLine) / 2;

        int displacement = -4*(64 - center);

        steeringAngle = -4*(64-center);
        
        std::string s = std::to_string(center)+"\t"+ std::to_string(steeringAngle)+"\n";
    }

    void steerLoop(){
        while(1) {
            calculateSteer();
            Car::servo = steeringAngle/100.;
            ThisThread::sleep_for(10ms);
        }
    }
}