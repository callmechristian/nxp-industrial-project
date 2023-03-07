#include "mbed.h"
#include <iostream>

#define BLINKING_RATE     500ms
PwmOut foo(D3);

 int RearMotor()
 {


    char str1[2];
    PwmOut foo(D3);

    foo.period(0.00004f);

    while(true)
    {

        scanf("%2s",str1);
        printf("atoi: %d\n", atoi(str1));

        float tmp = atoi(str1);
        tmp = tmp/100;

        foo.write(tmp);
        ThisThread::sleep_for(BLINKING_RATE);
    }


    return 0;
}