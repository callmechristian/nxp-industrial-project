#include "linescan.h"
#include "steering.h"


// PINS
DigitalOut led1(LED1);
DigitalOut clk(D13);
DigitalOut si(D10);
AnalogIn analogIn(A0);
// BufferedSerial serial(USBTX, USBRX); // tx, rx

// TODO: be able to use printf instead of serial.write: https://os.mbed.com/docs/mbed-os/v6.16/apis/serial-uart-apis.html
BufferedSerial serial(D1, D0); // tx, rx


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
            readAnalog();
            // sendReading();
            calculateSteer();
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

        wait_us(25000);
    }

    void sendReading()
    {
        int foo[128];
        for (int i = 0; i < 128; i++)
        {
            std::string s = std::to_string(cameraData[i])+",";
            // std::cout << s;
            serial.write(&s, s.size());
        }
        // std::cout << "," << std::endl;
        serial.write((char*)",\n",2);
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

}

