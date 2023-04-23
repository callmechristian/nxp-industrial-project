

// stl
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <iostream>



// our own libraries
#include "DigitalIn.h"
#include "PinNames.h"
#include "RearMotors.h"
#include "Camera.h"
#include "Servo.h"
#include "Steer.h"
#include "Ultrasonic.h"
// #include "linescan.h"
// #include "steering.h"

#include "Car.h"
#include "ThisThread.h"

namespace Car {
    // DEFINITIONS
    //      PINS

    // Camera
    DigitalOut led1(LED3);
    DigitalOut led2(LED1);

    DigitalOut clk(D13);
    DigitalOut si(D10);
    AnalogIn analogIn(A0);

    // Rear Motors
    Servo leftMotor(D4);
    Servo rightMotor(D5);

    InterruptIn up(D7);
    InterruptIn down(D8);

    // Servo
    Servo servo(D3);

    // Ultrasonic 
    DigitalOut trig(D11);
    DigitalIn echo(D12);


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

        // serialPC.sync();
        // serial.sync();

        // Initialize rearMotors
        // maybe not needed
        RearMotors::initializeRearMotors();
        // Initialize Servo
        Steer::initializeServo();
        // Initialize camera
        Camera::initialize();
        
        // start the threads
        steerThread.start(Steer::steerLoop);
        motorThread.start(RearMotors::motorLoop);
        cameraThread.start(Camera::cameraLoop);
        

        // ThisThread::sleep_for(2s);
        std::cout << "Start camera calibration" << std::endl;
        up.fall(&upPressed);
        down.fall(&downPressed);

        while(1)
        {   
            int dist = Ultrasonic::distance();

            if (dist < 20)
            {
                // std::cout << "EMERGENCY STOP" << std::endl;
                RearMotors::move(0);
                // break;
                ThisThread::sleep_for(2000ms);
                RearMotors::move(10);
            }
            
            ThisThread::sleep_for(1ms);
        }
        // Camera::calibrateCamera();
        std::cout << "Camera calibrated" << std::endl;

    }


    void upPressed() {
        led2 = !led2; // toggle the LED
        Camera::exposureTime = Camera::exposureTime + 5ms;
    }

    void downPressed() {
        led1 = !led1; // toggle the LED
        Camera::exposureTime = Camera::exposureTime - 5ms;
    }

    
}
