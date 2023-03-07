#include "BufferedSerial.h"
#include "PinNames.h"
#include "mbed.h"
#include "stdlib.h"
#include <iostream>

DigitalOut led1(LED1);
DigitalOut clk(D13);
DigitalOut si(D10);
AnalogIn camData(A0);
BufferedSerial pc(USBTX, USBRX); // tx, rx
// float PixelArray[128] ;  
int PixelArray[128] ;  
int sensorValue;

void plotImage(int array[])
{
    for (int i = 0; i < 129; i++)
    {
        if (array[i] == 1)
            std::cout << "1";
        else
            std::cout << ".";
    }
    std::cout << "\n";
}

void scan()
{
//     digitalWrite(SI, HIGH);
//  digitalWrite(CLK, HIGH);
//  digitalWrite(SI, LOW);
//  digitalWrite(CLK, LOW);
    si.write(1);
    clk.write(1);
    si.write(0);
    clk.write(0);

    for(int i = 0; i < 128; i ++){
        clk.write(1);
        clk.write(0);
    }
    sensorValue = camData.read()*3.3f;   // Get value for saturation time.
    std::cout << sensorValue << std::endl;
    while(1)
    {


    //11111111111111111111111111111111
    si.write(1);
    clk.write(1);
    si.write(0);
    clk.write(0);
    //11111111111111111111111111111111  
    
    
    //222222222222222222222222222222222222222222222222222222222222222222
    for(int i = 0; i < 129; i ++){
        // ThisThread::sleep_for(sensorValue);    //  saturation time
        clk.write(1);
        wait_us(7);    
        // PixelArray[i] = int(camData.read()*100);
        PixelArray[i] = int(camData.read()*100) > 90 ? 1 : 0;
        // printf("%d\n", int(camData.read()*100));
        
        clk.write(0);
    }
    //222222222222222222222222222222222222222222222222222222222222222222
    
    
    //333333333333333333333333333333333333333
    // for(int i = 0; i < 129; i ++){
    //     printf("%d, ", PixelArray[i]);
    //     // std::cout << PixelArray[i] << ",";
    // }
    // std::cout << "\n" << std::endl;
    plotImage(PixelArray);
    // ThisThread::sleep_for(1000ms);
    }
}

void scan_2()
{
int ADCdata [128];
float slopeAccum;
float slopeCount;
float approxPos;
float minVal;

int minLoc;

float straight = 0.00155f;
float hardLeft = 0.0013f;
float slightLeft = 0.00145f;
float hardRight = 0.0018f;
float slightRight = 0.00165f;

float currDirection = straight;
    //servo.period(SERVO_FREQ);
    int integrationCounter = 0;
    
    while(1) {
            
        if(integrationCounter % 151== 0){
            //__disable_irq
            si = 1;
            clk = 1;
            //wait(.00001);
            si = 0;
            clk = 0;
            integrationCounter = 0;
            
            slopeAccum = 0;
            slopeCount = 0;
            approxPos = 0;
                
        }
        else if (integrationCounter > 129){
            plotImage(ADCdata);
            ThisThread::sleep_for(1000ms);

            minVal = ADCdata[15];
            for (int c = 15; c < 118; c++) {
                if (ADCdata[c] < minVal){
                    minVal = ADCdata[c];
                    minLoc = c;
                }
            }
            
            for (int c = 15; c < 118; c++) {
                if (ADCdata[c] >= minVal && ADCdata[c] - minVal < 0.04f && ADCdata[c] > 0.1f){
                    slopeAccum += c;
                    slopeCount++;
                }
            }
            
            approxPos = (float)slopeAccum/(float)slopeCount;
            
            if(approxPos > 0 && approxPos <= 20){
                    // servo.pulsewidth(hardLeft);
            } else if (approxPos > 20 && approxPos <= 45){
                    // servo.pulsewidth(slightLeft);
            } else if (approxPos > 45 && approxPos <= 90){
                // servo.pulsewidth(straight);
            } else if (approxPos > 90 && approxPos <= 105){
                // servo.pulsewidth(slightRight);
            } else if (approxPos > 105 && approxPos <= 128){
                    // servo.pulsewidth(hardRight);
            }
            integrationCounter = 150;
        }
        else{
            clk = 1;
            wait_us(70);
            ADCdata[integrationCounter - 1] = int(camData.read()*100) > 90 ? 1 : 0;
            clk = 0;

        }

        //clk = 0;
        integrationCounter++;
        //camData.
        
    }
}
