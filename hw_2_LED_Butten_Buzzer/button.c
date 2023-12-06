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

//fd와 msgID를 전역 변수로 선언
int fd;
int msgID;
pthread_t buttonTh_id;

static void *buttonThFunc(void *arg);

int probeButtonPath(char *buttonPath)
{
    //해당 함수 작성 필요
    return 0;
}
int buttonInit(void)
{
    /********fd와 msgID를 지역변수(local variable)로 선언할 경우 이 부분 활성화****
    int fd;     
    int msgID;  
    ***************************************************************/
    char buttonPath[256];

    if (probeButtonPath(buttonPath) == 0 )
        return 0;
    fd=open (buttonPath, O_RDONLY);
    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}

static void *buttonThFunc(void *arg)
{
    (void)arg;      //사용되지 않은 변수 경고 suppress
    struct input_event stEvent;

while(1){
// Read from the input device node in blocking mode
        ssize_t bytesRead = read(fd, &stEvent, sizeof(struct input_event));

        if (bytesRead == sizeof(struct input_event)) {
            // EV_KEY 이벤트가 발생했는지 확인(키 누름 or 뗌)
            if (stEvent.type == EV_KEY) {
                // 키가 눌렸는지 확인 (버튼 누름)
                if (stEvent.value == 1) {
                    struct BUTTON_MSG_T message;
                    // 버튼 누름 확인, 메시지 보내기
                    struct msgbuf message;
                    message.mtype = 1;
                    message.mtext = "Button Pressed";   //메시지 내용
                    msgsnd(msgID, &message, sizeof(struct msgbuf), 0);
                }
            }
        }
    
}
return NULL;
}

int buttonExit(void)
{
    // Implementation for cleaning up and exiting the button functionality
    close(fd);
    pthread_join(buttonTh_id, NULL);    //버튼 쓰레드 종료 대기

    return 0;
}