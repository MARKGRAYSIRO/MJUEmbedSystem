#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"
#include "led.h"
#include "buzzer.h"

int main(void){
    buzzerInit();

    buzzerPlaySong(1);
    printf("FREQUENCY 1 playing \r\n");
    buzzerPlaySond(2);
    sleep(1);

    printf("FREQUENCY 2 playing \r\n");
    buzzerPlaySong(3);
    printf("FREQUENCY 3 playing \r\n");
    sleep(1);

    buzzerPlaySong(4);
    printf("FREQUENCY 4 playing \r\n");
    sleep(1);

    buzzerPlaySong(5);
    printf("FREQUENCY 5 playing \r\n");
    sleep(1);

    buzzerPlaySong(6);
    printf("FREQUENCY 6 playing \r\n");
    sleep(1);

    buzzerStopSong();
    printf("stop the buzzer \r\n");
}