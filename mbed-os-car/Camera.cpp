#include "ThisThread.h"

#include "Camera.h"
#include "mbed.h"
#include "Car.h"
#include <iostream>
#include <string>

#include "Steer.h"


// Exposure rate in milliseconds
#define EXPOSURE_TIME     25ms

using namespace Car;

namespace Camera{
    int cameraData[128];  
    Kernel::Clock::duration_u32 exposureTime = 25ms;

    bool calibrated = false;

    // int steeringAngle = 50;

    void cameraLoop()
    {
        while(1)
        {
            readAnalog();
            sendReading();
        }
    }
    
    // CANERA FUNCTIONS
    void clockPulse()
    {
        wait_us(1);
        clk.write(1);
        clk.write(0);
    }

    void initialize()
    {
        for (int i = 0; i < 128; i++)
        {
            clockPulse();
        }

        si.write(1);
        clk.write(1);
        si.write(0);
        clk.write(0);

        for (int i = 0; i < 128; i++)
        {
            clockPulse();
        }
    }

    void readAnalog()
    {
        // Start integration cycle by sending SI pulse
        si.write(1);
        clk.write(1);
        si.write(0);
        clk.write(0);


        // ?? delay ??
        wait_us(20);

        cameraData[0] = 4095-int(analogIn.read()*4095);

        for (int i = 0; i < 128; i++)
        {
            wait_us(10);

            cameraData[i] = 4095-int(analogIn.read()*4095);
            clockPulse();
        }

        ThisThread::sleep_for(exposureTime);
    }

    void sendReading()
    {
        for (int i = 0; i < 128; i++)
        {
            std::string s = std::to_string(cameraData[i])+",";
            
            // serial.write(&s, s.size());
            serialPC.write(&s, s.size());
            
        }
        // serial.write((char*)",\n",2);
        serialPC.write((char*)",\n",2); 
    }
    

    void calibrateCamera(){
        // IDEA:
            // find the darkest pixel, increase exposure time, recursively run function again, until exposure time too high and all pixels are white, then decrease exposure time by a fraction and set Steer::threshold to maybe 10% of the highest pixel value

        std::cout << "Calibrating" << std::endl;

        if (!calibrated)
        {
            int maxVal = 0;
            int sum = 0;
            int count = 0;
            float mean = 0;

            for (int i = 0; i < 128; i++)
            {
                if (Camera::cameraData[i] > maxVal){
                    maxVal = Camera::cameraData[i];
                    if (Camera::cameraData[i]>0)
                    {
                        sum += Camera::cameraData[i];
                        count++;
                    }
                }
            }
            mean = float(sum) / count;
            std::cout << std::to_string(int(mean)) << std::endl;

            // if (maxVal == 0)
            // {
            //     exposureTime = exposureTime/10;
            //     calibrated = true;
            // }
            // else
            // {
            //     exposureTime = 5*exposureTime;
            // }
            // printf("calibrated %d\n", exposureTime.count());
            // calibrateCamera();
        }
        
        int leftLine=0;
        int rightLine=0;
        
        // find right line
        // for (int i = 64; i < 128; i++)
        // {
        //     if (Camera::cameraData[i] > Steer::threshold){
        //         rightLine = i;
        //         break;
        //     }
        // }

        // // find left line
        // for (int i = 64; i > 0; i--)
        // {
        //     if (Camera::cameraData[i] > Steer::threshold){
        //         leftLine = i;
        //         break;
        //     }
        // }

        
        // if (leftLine == 0 || rightLine == 0)
        // {
        //     Steer::threshold = Steer::threshold/10;
        //     calibrateCamera();
        // }

        // if (float(Steer::threshold)/cameraData[leftLine] > 0.6 || float(Steer::threshold)/cameraData[rightLine] > 0.6)
        // {
        //     Steer::threshold = Steer::threshold*0.5;
        //     calibrateCamera();
        // }



    }
}

