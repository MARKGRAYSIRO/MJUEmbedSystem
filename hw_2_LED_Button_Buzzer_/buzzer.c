#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_SCALE_STEP          8
#define BUZZER_BASE_SYS_PATH    "/sys/bus/platfor/devices/"
#define BUZZER_FILENAME         "peribuzzzer"
#define BUZZER_ENABLE_NAME      "enable"
#define BUZZER_FREQUENCY_NAME   "frequency"
char gBuzzerBaseSysDir[128];
const int musicScale[MAX_SCALE_STEP] =
{
    262,294,330,349,392,440,494,523
};

int buzzerInit(void){

}

int buzzerPlaySong(int scale){

}

int buzzerStopSong(void){

}

int buzzerExit(void){
    
}