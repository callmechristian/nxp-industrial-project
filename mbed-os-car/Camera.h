#pragma once

#include <vector>

namespace Camera {
    // VARIABLES
    extern std::vector<int> cameraData;  
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