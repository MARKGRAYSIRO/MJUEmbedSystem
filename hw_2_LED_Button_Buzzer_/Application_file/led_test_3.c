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

int main(void){
    ledLibInit();
    
    ledOnOff(7, 1);
    sleep(1);
    ledOnOff(6, 1);
    sleep(1);
    ledonfOff(5, 1);

    ledLibExit();
}