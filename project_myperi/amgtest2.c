#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "accelMagGyro.h"

int main(void){

    for(int i =0; i <100;i++){
    printAccel();
    printMag();
    printGyro();
    usleep(1000000);
    }

    return 0;
}