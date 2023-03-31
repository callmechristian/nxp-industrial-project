

// stl
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <iostream>



// our own libraries
#include "RearMotors.h"
#include "Camera.h"
#include "Servo.h"
#include "Steer.h"
// #include "linescan.h"
// #include "steering.h"

#include "Car.h"

namespace Car {
    // DEFINITIONS
    //      PINS

    // Camera
    DigitalOut led1(LED1);
    DigitalOut clk(D13);
    DigitalOut si(D10);
    AnalogIn analogIn(A0);

    // Rear Motors
    Servo motor_l(D4);
    Servo motor_r(D5);

    // Servo
    Servo servo(D3);

    // Serial communication
    BufferedSerial serialPC(USBTX, USBRX); 
    BufferedSerial serial(D1, D0);

    // threads
    Thread steerThread;
    Thread motorThread;
    Thread cameraThread;


    // using namespace RearMotors;

    // using namespace Camera;

    void MainCarLoop(){
        // Initialize serial communication
        serial.set_baud(115200);
        serialPC.set_baud(115200);

        // Initialize rearMotors
        // maybe not needed
        RearMotors::initializeRearMotors();
        // Initialize Servo
        Steer::initializeServo();
        // Initialize camera
        Camera::initialize();

        ThisThread::sleep_for(1s);
        
        // start the threads
        steerThread.start(Steer::steerLoop);
        motorThread.start(RearMotors::motorLoop);
        cameraThread.start(Camera::cameraLoop);
        
    }
}
