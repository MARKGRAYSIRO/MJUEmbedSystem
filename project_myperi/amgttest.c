#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "accelMagGyro.h"

int main(void){

int mag[3];
float magSum =0;
    for(int i =0; i <100;i++){
    getMag(mag);

    mag[0] = (mag[0]>0)? mag[0]: -mag[0];
    mag[1] = (mag[1]>0)? mag[1]: -mag[1];
    mag[2] = (mag[2]>0)? mag[2]: -mag[2];

    magSum = mag[0] + mag[1] + mag[2];
    usleep(1000000);

    printf("%f\r\n", magSum);
    }

    return 0;
}