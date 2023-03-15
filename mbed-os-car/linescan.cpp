#include "linescan.h"
#include "steering.h"
#include <string>


// PINS
DigitalOut led1(LED1);
DigitalOut clk(D13);
DigitalOut si(D10);
AnalogIn analogIn(A0);
BufferedSerial serialPC(USBTX, USBRX); // tx, rx /

// TODO: be able to use printf instead of serial.write: https://os.mbed.com/docs/mbed-os/v6.16/apis/serial-uart-apis.html
BufferedSerial serial(D1, D0); // tx, rx
#include "Servo.h" 



namespace Camera{
    // VARIABLES
    int cameraData[128];  
    int sensorValue;

    // CONTINOUS SCAN
    void continousScan()
    {
        initialize();

        while(1)
        {
            // std::cout << "efijfpa" << std::endl;
            readAnalog();
            // sendReading();

            // wait_us(1000000);
            // calculateSteer(cameraData);
            steer();
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

        // wait_us(25000);
        wait_us(25);
    }

    void sendReading()
    {
        int foo[128];
        for (int i = 0; i < 128; i++)
        {
            std::string s = std::to_string(cameraData[i])+",";

            // std::cout << s;
            serial.write(&s, s.size());
            serialPC.write(&s, s.size());
        }
        // std::cout << "," << std::endl;
        serial.write((char*)",\n",2);
        serialPC.write((char*)",\n",2);
        // serial.write((int*) foo, 4*128);
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

    void steer(){
        bool leftLineFound=false;
            bool rightLineFound=false;

            int leftLine=0;
            int rightLine=0;
            signed int center=0;

            std::string s;
            for (int i = 0; i < 128; i++)
            {
            s = std::to_string(cameraData[i])+",";

            // std::cout << s;

            // serialPC.write(&s, s.size());
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

            Servo::steer(int(normalized*100));
            // serialPC.write((char*)",\n",2);

            // std::cout << s;

            // std::cout << "ste: " << std::to_string(int(normalized*100)) << std::endl;
            // wait_us(100);
    }

}

