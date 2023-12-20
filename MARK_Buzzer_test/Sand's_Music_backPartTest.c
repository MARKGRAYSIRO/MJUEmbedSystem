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

#define BPM  250000;


void rest(float beat) {
    int usecond = beat * BPM;
    buzzerEnable(0);
    usleep(usecond);
    buzzerEnable(1);
}
void beat(float beat) {
    int usecond = beat * BPM;
    usleep(usecond);
}


void frontLine() {
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //2마디
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //3마디
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);

    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //2마디
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //3마디
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //4마디
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //2마디
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //3마디
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //4마디
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //2마디
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //3마디
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //4마디
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(6);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //2마디
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(4);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //3마디
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(3);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
    
    //4마디
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(2);
    beat(0.4);
    rest(0.1);
    buzzerPlaySong2(18);
    beat(0.4);
    rest(0.6);
    buzzerPlaySong2(13);
    beat(0.4);
    rest(0.6);
    
    
    rest(0.5);
    buzzerPlaySong2(12);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(11);
    beat(0.4);
    rest(0.1);
    
    rest(0.5);
    buzzerPlaySong2(9);
    beat(1);
    buzzerPlaySong2(6);
    beat(0.5);
    buzzerPlaySong2(9);
    beat(0.5);
    buzzerPlaySong2(10);
    beat(0.4);
    rest(0.1);
}

int main() {
    buzzerInit();
    
    frontLine();
    frontLine();
    
    buzzerStopSong();
}
// 1시 2 도 3도# 4레 5레# 6미 7파 8파# 9솔 10솔# 11라 12라# 13시 14도 15도# 16레 17레#
// 18미
