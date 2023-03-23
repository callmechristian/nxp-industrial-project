#include "Steer.h"
#include <vector>
#include "Camera.h"
#include <iostream>
#include "ThisThread.h"
#include "Car.h"

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

        int THRESHOLD = 500;
        int leftLine=0;
        int rightLine=0;
        std::vector<int> over;

        for (int i = 0; i < 128; i++)
        {
            if (Camera::cameraData[i] > THRESHOLD){
                over.push_back(i);
            }
        }

        int sumL = 0;
        int countL = 0;
        int sumR = 0;
        int countR = 0;
        for (auto el : over){
            if (el<64){
                sumL+=el;
                countL++;
            }else{
                sumR+=el;
                countR++;
            }
        }
        

        leftLine = sumL/countL;
        rightLine = sumR/countR;

        int center = (leftLine + rightLine) / 2;
        // serial.write(&s, s.size());
        int displacement = -4*(64 - center);
        // angle_ = int((double(64+displacement)/128.0)*150);
        steeringAngle = 50+displacement;
        
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