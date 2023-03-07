#include "BufferedSerial.h"
#include "PinNames.h"
#include "mbed.h"
#include "stdlib.h"
#include <iostream>
#include <string>


namespace Camera {
    // VARIABLES
    extern int cameraData[128] ;  

    // UTILITY FUNCTIONS
    void plotImage(int array[]);

    // CAMERA FUNCTIONS
    void clockPulse();

    void initialize();

    void readAnalog();

    void sendReading();

    // CONTINOUS SCAN
    void continousScan();
}

