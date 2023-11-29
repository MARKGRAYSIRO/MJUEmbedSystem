#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"
#define LED_DRIVER_NAME "/dev/periled"

int main(int argc, char **argv){
    unsigned int data = 0;
    int i = 0;
    int onoff = 0;

    int ledLibInit(void);

    data = strtol(argv[1],NULL,16);

    while(1)
    {
    onoff = !onoff;
    sleep(data);
    for(i=1 ; i < 8 ; i++){
    int ledOnOff (i,onoff);
    }
    }

    atexit(ledLibExit);
    
    return 0;
}