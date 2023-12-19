#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "led.h"

static unsigned int ledValue = 0;
static int fd = 0;

int ledLibInit(void){
    fd=open("/dev/periled",O_WRONLY);
    ledValue = 0;
    if(fd < 0){
        printf("ledLibInit failed");
        return -1;
    }
    return 0;
}

int ledLibExit(void){
    ledValue = 0;
    ledOnOff(0,0);
    close(fd);
}

int ledOnOff (int ledNum, int onoff)
{
    int i=1;
    i = i<<ledNum; 
    ledValue = ledValue& (~i);
    if (onoff != 0) ledValue |=i;
    write (fd, &ledValue,4);
}

int ledstatus (void){
    return ledValue;
}