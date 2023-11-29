#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST  "/dev/input/event"
#define PROBE_FILE         "/proc/bus/input/devices"
#define HAVE_TO_FIND_1     "N: Name=/"ecube-button\"\n"
#define HAVE_TO_FIND_2     "H: Handlers=kbd event"

pthread_t buttonTh_id;
int flag = 0;

int probeButtonPath(char *newPath){
    int returnValue = 0;
    int number = 0;
    FLIE *fd = fopen(PROBE_FILE, "rt");
    #define HAVE_TO_FIND_1 "N: Name=/"ecube-button\"\n"
    #define HAVE_TO_FIND_2 "H: Handlers=kbd event"
    while(!feof(fd)){
        char tmpStr[200];
        fgets(tmpStr, 200. fd);
        if(strcmp(tmpStr, HAVE_TO_FIND_1) == 0){
            printf("YES! I found!: %s\r\n", tmpStr);
            returnValue = 1;
        }
        if((returnValue == 1)&&(strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0)){
            printf("-->%s", tmpStr);
            printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
            number = tmpStr[strlen(tmpStr)-3] - '0';
            //ascii charavter '0' - '9'
            //to interger(0)
            break;
        }
    }
    fclose(fd);
    if (returnValue == 1)
    sprintf(newPath,"%s%d", INPUT_DEVICE_LIST, number);
return returnValue;
}

int buttonInit(void)
{
    if (probeButtonPath(buttonPath) == 0 )
        return 0;
    fd=open (buttonPath, O_RDONLY);
    flag = 0;
    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}

// 이걸 사용하는 application에서는 msgid만 만들고 읽어 드리기만 하면 된다.
void *buttonTHFunc(void *arg){
    int readsize = 0;
    struct input_event stEvent;
    struct BUTTON_MSG_T button;
    while(!flag){
        readsize = read(fd, &stEvent, sizeof(stEvent));
        // 읽을 때 까지 버튼이 눌릴 때 까지 기다린다.
        if(readsize != sizeof(stEvent)){
            continue;
        }
        // key_pad가 눌렸다.
        if( stEvent.type == EV_KEY){
            switch(stEvent.code){
                case KEY_VOLUMEUP   : button.keyInput = 1;
                case KEY_HOME       : button.keyInput = 2;
                case KEY_SEARCH     : button.keyInput = 3;
                case KEY_BACK       : button.keyInput = 4;
                case KEY_MENU       : button.keyInput = 5;
                case KEY_VOLUMEDOWN : button.keyInput = 6;
            }
        if( stEvent.value == 0) button.pressed = 0;
        else                    button.pressed = 1;
        }
        button.messgeNum = 1;
        if(msgsnd(msgID, &button, sizeof(botton)-8,0) == -1)
        {
            prinx`tf("megsend error!\r\n");
            break;
        }

    }
}

int buttonExit(void){
    close(fd); 
    flag = 1; // 쓰레드 무한루프 종료
    pthread_join(buttonTh_id, NULL); 
    
}
