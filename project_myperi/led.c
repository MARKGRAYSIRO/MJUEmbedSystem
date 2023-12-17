#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "led.h"

static unsigned int ledValue = 0;
static int fd = 0;

int ledOnOff (int ledNum, int onoff){
    int i = 1;
    i = i << ledNum;
    ledValue = ledValue & (~i);
    if (onoff != 0) ledValue |= i;
    write (fd, &ledValue, 4);
}

int ledLibInit(void){
    fd=open("/dev/periled",O_WRONLY);
    if(fd < 0){
        printf("driver (//dev//cnled) open error.\n");
        return 1;
    }
    ledValue = 0;
}

int ledLibExit(void){
    ledValue = 0;
    ledOnOff(0,0);
    close(fd);
}

void ledCountdown(int count){
	ledLibInit();
    ledValue = 0;
    // count 만큼 LED를 켠다.
    for (int i = 0; i < count; i++) {
        ledOnOff(i, 1);  // i번째 LED를 켠다.
    }

    // LED를 하나씩 끈다.
    for (int i = count - 1; i >= 0; i--) {
		 sleep(1);
        ledOnOff(i, 0);  // i번째 LED를 끈다.
               // 1초 대기
	}
	ledLibExit();
}

int ledstatus (void){
    return ledValue;
}
