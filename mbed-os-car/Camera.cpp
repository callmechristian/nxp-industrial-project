#include "ThisThread.h"

#include "Camera.h"
#include "mbed.h"
#include "Car.h"
#include <iostream>


// Exposure rate in milliseconds
#define EXPOSURE_TIME     25ms

using namespace Car;

namespace Camera{
    int cameraData[128];  
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

        ThisThread::sleep_for(EXPOSURE_TIME);
    }

    void sendReading()
    {
        for (int i = 0; i < 128; i++)
        {
            std::string s = std::to_string(cameraData[i])+",";
            
            serial.write(&s, s.size());
            
        }
        serial.write((char*)",\n",2);
    }
    

    void calibrateCamera(){

    }
}

