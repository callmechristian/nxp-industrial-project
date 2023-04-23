// mbed libraries
#include "InterfaceDigitalOut.h"
#include "PinNames.h"
#include "mbed.h"
#include "ThisThread.h"
#include "BufferedSerial.h"

// imported libraries
#include "Servo.h"

namespace Car {
    // DECLARATIONS
    //      PINS

    // Camera
    extern DigitalOut led1;
    extern DigitalOut clk;
    extern DigitalOut si;
    extern AnalogIn analogIn;

    // Rear Motors
    extern Servo leftMotor;
    extern Servo rightMotor;

    // Servo
    extern Servo servo;

    // Ultrasonic
    extern DigitalOut trig;
    extern DigitalIn echo;

    // Serial communication
    extern BufferedSerial serialPC;
    extern BufferedSerial serial; // tx, rx

    void MainCarLoop();
    void upPressed();
    void downPressed();
}