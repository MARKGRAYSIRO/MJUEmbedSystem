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
#include "buzzer.h"

#define BPM  300000;

void beat(float beat) {
    int usecond = beat * BPM;
    usleep(usecond);
}
void rest(float beat) {
    int usecond = beat * BPM;
    buzzerEnable(0);
    usleep(usecond);
    buzzerEnable(1);
}
//1솔 2레# 3라#  4솔#  5파
int main() {
    buzzerInit();
    
    buzzerPlaySong2(1);
    beat(1);
    buzzerPlaySong2(2);
    beat(1);
    buzzerPlaySong2(3);
    beat(1.9);
    rest(0.1);
    
    buzzerPlaySong2(4);
    beat(0.3);
    rest(0.03);
    buzzerPlaySong2(4);
    beat(0.3);
    rest(0.03);
    buzzerPlaySong2(4);
    beat(0.3);
    rest(0.03);
    
    buzzerPlaySong2(5);
    beat(0.3);
    rest(0.03);
    buzzerPlaySong2(5);
    beat(0.3);
    rest(0.03);
    buzzerPlaySong2(4);
    beat(0.3);
    rest(0.03);
    
    buzzerPlaySong2(1);
    beat(2);
    
    buzzerStopSong();
}
