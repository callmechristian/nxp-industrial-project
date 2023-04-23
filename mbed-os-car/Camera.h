#pragma once

#include "mbed.h"
namespace Camera {
    // VARIABLES
    extern int cameraData[128] ;
    extern Kernel::Clock::duration_u32 exposureTime;

    extern bool calibrated;
    // extern int steeringAngle;
    
    // UTILITY FUNCTIONS
    

    // CAMERA FUNCTIONS
    void clockPulse();

    void initialize();

    void readAnalog();

    void sendReading();

    void cameraLoop();

    void calibrateCamera();

}