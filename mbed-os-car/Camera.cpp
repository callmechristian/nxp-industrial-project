#include "ThisThread.h"

#include "Camera.h"
#include "mbed.h"
#include "Car.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace Car;

namespace Camera{
    // dynamic camera exposure adjustment
    chrono::milliseconds exposureTimeStep = 1ms;
    
    // exposure rate in milliseconds
    chrono::milliseconds EXPOSURE_TIME = 25ms;
    
    std::vector<int> cameraData(128);  
    // int steeringAngle = 50;

    void cameraLoop()
    {
        calibrateCamera();
        
        while(1)
        {
            readAnalog();
            sendReading();
            
            // sleep for 1ms to not hog the processor
            ThisThread::sleep_for(1ms);
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

        ThisThread::sleep_for(EXPOSURE_TIME);
    }

    void sendReading()
    {
        for (int i = 0; i < 128; i++)
        {
            std::string s = std::to_string(cameraData[i])+",";
            
            serialPC.write(&s, s.size());
            
        }
        serialPC.write((char*)",\n",2);
    }
    

    void calibrateCamera(){
        // check if white is within desired range
        int whitePatchValue = cameraData[64];
        if (whitePatchValue > 500)
        {
            // increase exposure time
            EXPOSURE_TIME += exposureTimeStep;
        }
        else if (whitePatchValue < 0)
        {
            // decrease exposure time
            EXPOSURE_TIME -= exposureTimeStep;
        }
    }
}

