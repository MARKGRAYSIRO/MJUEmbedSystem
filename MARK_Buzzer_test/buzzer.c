#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP          18
#define BUZZER_BASE_SYS_PATH    "/sys/bus/platform/devices/peribuzzer."
#define BUZZER_ENABLE_NAME      "enable"
#define BUZZER_FREQUENCY_NAME   "frequency"
char gBuzzerBaseSysDir[128];
const int musicScale[MAX_SCALE_STEP] =
{// 샌즈용 도 ~ 솔
    262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,233
};
//{ 해리포터 용
//    247,262, 277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,233
//};



int buzzerInit(void){
    char str[128];
    char result;
    char *pdel;
    char *s;
    sprintf(str, "ls -d %s*", BUZZER_BASE_SYS_PATH);
    FILE* p = popen(str, "r");
    if (p == NULL){
        printf("popen fail \n");
        return -1;
    }
    // str ==> ex) /sys/bus/platform/devices/peribuzzer.30
    s = fgets(str, 128, p);
    if (s == NULL){
        printf("fgets fail\n");
        return -1;
    }
    pdel = strrchr(s,(int)'.');
    if(pdel == NULL){
        printf(". is not found\n");
        return -1;
    }
    int i = 0;
    while(1){
        if( pdel[i] == 0x0A){
            pdel[i] = 0;
            break;
        }
        i++;
    }
    sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,pdel+1);
}

void buzzerEnable(int en){
    char strshellcmd[150];
    if(en){
        sprintf(strshellcmd,"echo '1' > %s%s\n", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
        system(strshellcmd);
    }
    else{
        sprintf(strshellcmd,"echo '0' > %s%s\n", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
        system(strshellcmd);
    }
}

int buzzerPlaySong(int scale){
    char strshellcmd[150];
    sprintf(strshellcmd, "echo '%d' > %s%s\n", musicScale[scale-1], gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);
    system(strshellcmd);
    buzzerEnable(1);
    return 0;
}

int buzzerStopSong(void){
    buzzerEnable(0);
    return 0;
}

int buzzerExit(void){
    buzzerEnable(0);
}

void buzzerCountdown(int count){
    buzzerInit();
    int i =0;
    for(i =0; i< count; i++){
    buzzerPlaySong(3);
    usleep(100000);
    buzzerStopSong();
    usleep(900000);
    }
    buzzerExit();
}
