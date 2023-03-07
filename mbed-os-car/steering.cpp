#include "steering.h"
#include "linescan.h"
#include <string>
// using namespace N;

int THRESHOLD = 2000;

namespace Camera {
    void calculateSteer()
    {
        while(1)
        {
            bool leftLineFound=false;
            bool rightLineFound=false;

            int leftLine=0;
            int rightLine=0;
            int center=0;

            for (int i = 0; i < 128; i++)
            {
                if (cameraData[i] > THRESHOLD)
                {
                    // std::cout << "Black Pixel found at: " << std::to_string(i) << std::endl;


                    // 1. GET RIGHT MOST LEFT BLACK PIXEL
                        // 1.1 
                    if (!leftLineFound)
                    {
                        leftLine = i;
                    }
                    // 2. GET LEFT MOST RIGHT BLACK PIXEL
                    else {
                        rightLine = i;
                    }
                    // 3. SUM VALUES AND DIVIDE BY 2
                    center = (leftLine + rightLine) / 2;
                }
                else {
                    if (leftLine > 0)
                    {
                        leftLineFound = true;
                    }
                }
            }

            std::cout << "LeftLine: " << std::to_string(leftLine) << std::endl;
            std::cout << "RightLine: " << std::to_string(rightLine) << std::endl;
            std::cout << "Center: " << std::to_string(center)<< std::endl;
        }
    }
}
