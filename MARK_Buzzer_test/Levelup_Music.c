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

int main() {
    buzzerInit();
    
    buzzerPlaySong2(1);
    beat(1);
    buzzerPlaySong2(3);
    beat(1);
    buzzerPlaySong2(7);
    beat(1);
    
    buzzerPlaySong2(3);
    beat(1);
    buzzerPlaySong2(7);
    beat(1);
    buzzerPlaySong2(12);
    beat(1);
    
    buzzerStopSong();
}
// 1시 2 도 3도# 4레 5레# 6미 7파 8파# 9솔 10솔# 11라 12라# 13시 14도 15도# 16레 17레#
// 18미
