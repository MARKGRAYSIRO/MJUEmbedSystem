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

//1 시 2 도 3도# 4레 5레# 6미 7파 8파# 9솔 10솔# 11라 12라# 13시 14도 15도# 16레#


void beat(float beat) {
    int usecond = beat * 250000;
    usleep(usecond);
}

int main() {
    buzzerInit();
    
    buzzerPlaySong(1);
    beat(1);
    
    buzzerPlaySong(6);
    beat(1.5);
    buzzerPlaySong(9);
    beat(0.5);
    buzzerPlaySong(7);
    beat(1);
    
    buzzerPlaySong(6);
    beat(2);
    buzzerPlaySong(13);
    beat(1);
    
    buzzerPlaySong(11);
    beat(3);
    
    buzzerPlaySong(7);
    beat(3);
    
    
}

//int main(void){
//    buzzerInit();
//
//    buzzerPlaySong(1);
//    printf("FREQUENCY 1 playing \r\n");
//    buzzerPlaySong(2);
//    sleep(1);
//
//    printf("FREQUENCY 2 playing \r\n");
//    buzzerPlaySong(3);
//    printf("FREQUENCY 3 playing \r\n");
//    sleep(1);
//
//    buzzerPlaySong(4);
//    printf("FREQUENCY 4 playing \r\n");
//    sleep(1);
//
//    buzzerPlaySong(5);
//    printf("FREQUENCY 5 playing \r\n");
//    sleep(1);
//
//    buzzerPlaySong(6);
//    printf("FREQUENCY 6 playing \r\n");
//    sleep(1);
//
//    buzzerStopSong();
//    printf("stop the buzzer \r\n");
//}
