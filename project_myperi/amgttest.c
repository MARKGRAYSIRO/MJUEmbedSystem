#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "temperature.h"
#include "accelMagGyro.h"

int main(void){

    for(int i =0; i <100;i++){
    printAccel();
    printMag();
    printGyro();
    printTemp();
    usleep(1000000);
    }

    return 0;
}