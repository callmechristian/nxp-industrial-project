#include "linescan.h"
#include "ThisThread.h"
#include "steering.h"
#include <string>
#include <vector>
#include <mutex>
#include "Own_Servo.h"
#include "RearMotors.h"
#include "Servo/Servo.h"


// PINS
DigitalOut led1(LED1);
DigitalOut clk(D13);
DigitalOut si(D10);
AnalogIn analogIn(A0);
PwmOut pwm(D4);

// Servo new_servo(D3);

Servo steer_servo(D3);


// tx, rx /

// TODO: be able to use printf instead of serial.write: https://os.mbed.com/docs/mbed-os/v6.16/apis/serial-uart-apis.html
BufferedSerial serial(D1, D0); // tx, rx

Thread thread;

Thread thread2;



namespace Camera{
    BufferedSerial serialPC(USBTX, USBRX); 
    // VARIABLES
    int cameraData[128];  
    int cameraData_copy[128];  
    int sensorValue;
    Mutex m;
    int angle_;
    // std::map<std::string, std::string> g_pages;
    // std::mutex g_pages_mutex;
    // CONTINOUS SCAN
    void continousScan()
    {
        initialize();

        // Servo::initializeServo();

        serial.set_baud(115200);
        serialPC.set_baud(115200);
        // thread.start(callback(Servo::steer, angle_));
        angle_ = 50;
        
        thread.start(steer_thread);
        thread2.start(move_thread);

        // thread.start(led2_thread);
        // thread.start(sendReading);

        while(1)
        {
            // std::cout << "efijfpa" << std::endl;
            readAnalog();

            sendReading();
            // wait_us(10000000);
            // ThisThread::sleep_for(1s);
            // calculateSteer(cameraData);
            Filipposteer();
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
        // std::cout << std::endl;
        // serial.write((char*)",\n",2);
        // serialPC.write((char*)",\n",2);
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

        // wait_us(25000);
        std::copy(std::begin(cameraData), std::end(cameraData), std::begin(cameraData_copy));
        wait_us(25000);

        // wait_us(10000000);
    }

    void sendReading()
    {
        // while(true)
        // {
        //     m.lock();
            int foo[128];
            for (int i = 0; i < 128; i++)
            {
                std::string s = std::to_string(cameraData_copy[i])+",";

                //std::cout << s;
                serial.write(&s, s.size());
                // serialPC.write(&s, s.size());
            }

            //std::cout << std::endl;
            // std::cout << "," << std::endl;
            serial.write((char*)",\n",2);
            // serialPC.write((char*)",\n",2);
            // serial.write((int*) foo, 4*128);
            // ThisThread::sleep_for(1000ms);
        //     m.unlock();
        // }
        
    }


    // UTILITY FUNCTIONS
    void plotImage(int array[])
    {
        // std::cout << "StartArray";
        for (int i = 0; i < 129; i++)
        {
            std::cout << array[i];
            if (array[i] == 1)
                std::cout << "1";
            else
                std::cout << ".";
        }
        // std::cout << "EndArray";
        std::cout << "\n";
    }

    void Filipposteer(){
        
        int THRESHOLD = 50;
        int leftLine=0;
        int rightLine=0;
        std::vector<int> over;

        for (int i = 0; i < 128; i++)
        {
            if (cameraData[i] > THRESHOLD){
                over.push_back(i);
            }
        }

        int sumL = 0;
        int countL = 0;
        int sumR = 0;
        int countR = 0;
        for (auto el : over){
            if (el<64){
                sumL+=el;
                countL++;
            }else{
                sumR+=el;
                countR++;
            }
        }
        

        leftLine = sumL/countL;
        rightLine = sumR/countR;

        int center = (leftLine + rightLine) / 2;
        // serial.write(&s, s.size());
        int displacement = -4*(64 - center);
        // angle_ = int((double(64+displacement)/128.0)*150);
        angle_ = 50+displacement;
        
        std::string s = std::to_string(center)+"\t"+ std::to_string(angle_)+"\n";
        // serialPC.write(&s, s.size());

        // initializeServo();
        // std::cout << "L: " << std::to_string(leftLine) << "\tR: " << std::to_string(rightLine) << "\tC: " << std::to_string(rightLine) << std::endl;


    }
     void move(int speed){ //speed between 42 and 56
        //need to map!! 42 - 56
        float tmp = speed;
        tmp = tmp/100;
        pwm.write(tmp);
    } 

    void move_thread(){
        // pwm.period(0.00004f);
        // // pwm.write(10);
        // std::cout << "before init" << std::endl;
    
        // ThisThread::sleep_for(5s);
        // pwm.write(0.38);

        // std::cout << "before init" << std::endl;

        // ThisThread::sleep_for(100ms);
        // pwm.write(0.42);
        // while(true)
        // {
        // }

        RearMotors::initializeRearMotors();

        RearMotors::move(52);
        
        ThisThread::sleep_for(10s);
        // while(true)
        // {

        // }
        
    }

    void steer_thread(){
        // pwm.write(10);
        // pwm.period(0.00004f);
        // pwm.period(0.020f);

        // // pwm.write(10);
        // std::cout << "before init" << std::endl;
    
        // ThisThread::sleep_for(5s);
        // pwm.write(0.38);
        // ThisThread::sleep_for(100ms);
        // pwm.write(0.42);

        // while(true){
        //     // std::cout << "steer and move" << std::endl;

        //     // RearMotors::move(43);
        //     // ThisThread::sleep_for(100ms);

        //     // Servo::steer(angle_);
        //     ThisThread::sleep_for(10ms);
        // }


        ThisThread::sleep_for(3s);


        std::cout<<"Calibrating..."<<std::endl;
        steer_servo.calibrate();

        std::cout<<"Done."<<std::endl;

        std::cout<<"Steering to 0.3"<<std::endl;
        steer_servo = 0.3;
        while(1) {
            // std::cout<<"Steering to " << std::to_string(int(angle_)) <<std::endl;
            steer_servo = angle_/100.;
            ThisThread::sleep_for(10ms);
            // for(int i=0; i<100; i++) {
            //  steer_servo = i/100.0;
            //     ThisThread::sleep_for(10ms);
            // }
            // for(int i=100; i>0; i--) {
            //     steer_servo = i/100.0;
            //     ThisThread::sleep_for(10ms);
            // }
        }
        
    }

    void steer(){
        bool leftLineFound=false;
        bool rightLineFound=false;

        int leftLine=0;
        int rightLine=0;
        signed int center=0;
        // sendReading();
        std::string s;
        for (int i = 0; i < 128; i++)
        {
            s = std::to_string(cameraData[i])+",";

            // std::cout << std::to_string(cameraData[i]) << ", ";
            if (cameraData[i] > 50)
            {
                // std::cout << "Black Pixel found at: " << std::to_string(i) << std::endl;

                // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
                // 1. GET RIGHT MOST LEFT BLACK PIXEL
                    // 1.1 
                if (!leftLineFound)
                {
                    // std::cout << "+++++++++++++++++++++++++" << std::endl;

                    leftLine = i;
                }
                // 2. GET LEFT MOST RIGHT BLACK PIXEL
                else {
                    rightLine = i;

                    break;
                }
                // 3. SUM VALUES AND DIVIDE BY 2
                
            }
            else {
                if (leftLine > 0)
                {
                    leftLineFound = true;
                }
            }
        }

        center = (leftLine + rightLine) / 2;

        if (rightLine == 0)
        {
            if (leftLine > 64)
            {
                center = leftLine + 64;
                // displacement = 100;
                
            }
            else 
            {
                center = leftLine - 64;
                // displacement = -100;
            }
        }

        serialPC.write((char*)",\n",2);
        double displacement = 64-center;
        double normalized = displacement/64;
        // s = "normalized: ";
        s = std::to_string(int(displacement))+"\n";

        // std::cout << s;
        // serialPC.write(&s, s.size());

        // serialPC.write(&s, s.size());
        // serialPC.write((char*)",\n",2);
        // s = std::to_string(int(normalized*100));
        // serialPC.write(&s, s.size());
        std::cout << "leftline: " << leftLine << std::endl;
        std::cout << "rightline: " << rightLine << std::endl;
        std::cout << "center: " << center << std::endl;

        //Servo::steer(int(normalized*100));
        // serialPC.write((char*)",\n",2);

        // std::cout << s;

        // std::cout << "ste: " << std::to_string(int(normalized*100)) << std::endl;
        // wait_us(100);
    }

}

