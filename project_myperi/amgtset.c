#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "accelMagGyro.h"

static pthread_t AccelTh_ID;
static int ACCEL[3];
int stopFlag = 0;

void *GetAccelThFunc(void *arg){
    while(!stopFlag){
    getAccel(ACCEL);
    printf("%d, %d, %d",ACCEL[0],ACCEL[1],ACCEL[2]);
    usleep(100000);
    }
}

int main(void){
    printf("if you want to stop, just input 1 >>\t");
    pthread_create(&AccelTh_ID,NULL, GetAccelThFunc,NULL);
    pthread_detach(AccelTh_ID);
    sleep(10);
    stopFlag = 1;

    return 0;
}