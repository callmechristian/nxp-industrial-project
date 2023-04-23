#include "Steer.h"
#include <vector>
#include "Camera.h"
#include <iostream>
#include "ThisThread.h"
#include "Car.h"

namespace Steer{
    int steeringAngle = 50;
    int threshold = 500;

    void initializeServo(){
        ThisThread::sleep_for(3s);

        std::cout<<"Calibrating Servo..."<<std::endl;
        Car::servo.calibrate();

        std::cout<<"Done."<<std::endl;

        // std::cout<<"Steering to 0.3"<<std::endl;
        // Car::servo = 0.3;
    }

    void calculateSteer(){
        // TODO: if no pixel over threshold, change saturation or lower threshold
        // int leftLine=-1;
        // int rightLine=-1;
        
        // // find right line
        // for (int i = 64; i < 128; i++)
        // {
        //     if (Camera::cameraData[i] > threshold){
        //         rightLine = i;
        //         break;
        //     }
        // }

        // // find left line
        // for (int i = 64; i > 0; i--)
        // {
        //     if (Camera::cameraData[i] > threshold){
        //         leftLine = i;
        //         break;
        //     }
        // }

        // int center = (leftLine + rightLine) / 2;
        // // serial.write(&s, s.size());
        // float kp = -1.5;
        // float displacement = kp*(64 - center);
        // // if (displacement < 4){
        // //     return;
        // // }
        // if (leftLine == -1)
        // {
        //     displacement = -1.5*30;
        // }
        // else if(rightLine == -1)
        // {
        //     displacement = 1.5*30;
        // }
        
        int leftLine=0;
        int rightLine=0;
        std::vector<int> over;

        for (int i = 0; i < 128; i++)
        {
            if (Camera::cameraData[i] > threshold){
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
        int kp = -4;
        int displacement = kp*(64 - center);
        // angle_ = int((double(64+displacement)/128.0)*150);
        steeringAngle = 50+displacement;
        
        std::string s = std::to_string(center)+"\t"+ std::to_string(steeringAngle)+"\n";
        // ThisThread::sleep_for(1ms);
    }

    void steerLoop(){
        while(1) {
            calculateSteer();
            Car::servo = steeringAngle/100.;
            ThisThread::sleep_for(10ms);
        }
    }
} // namespace Steer