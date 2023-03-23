#pragma once

namespace Camera {
    // VARIABLES
    extern int cameraData[128] ;  
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