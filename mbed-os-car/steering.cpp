#include "steering.h"
#include "linescan.h"
#include "mbed_wait_api.h"
#include <ios>
#include <string>
// using namespace N;

int THRESHOLD = 50;

namespace Camera {
    void calculateSteer(const int (&cameraData_)[128])
    {
        // while(1)
        // {
            bool leftLineFound=false;
            bool rightLineFound=false;

            int leftLine=0;
            int rightLine=0;
            signed int center=0;

            for (int i = 0; i < 128; i++)
            {
                std::cout << std::to_string(cameraData_[i]) << ", ";
                if (cameraData_[i] > THRESHOLD)
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

            double displacement = 64-center;
            double normalized = displacement/64;

            // should be 6
            std::cout << "LeftLine: " << std::to_string(leftLine) << std::endl;
            // should be 121 or something
            std::cout << "RightLine: " << std::to_string(rightLine) << std::endl;
            std::cout << "Center: " << std::to_string(center)<< std::endl;
            // wait_us(1000000);
        }
    // }
}
