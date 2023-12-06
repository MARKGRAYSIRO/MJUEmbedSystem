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

int buttonInit(void)
{
    if (probeButtonPath(buttonPath) == 0 )
        return 0;
    fd=open (buttonPath, O_RDONLY);
    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}

while(1){
// Read from the input device node in blocking mode
        ssize_t bytesRead = read(fd, &stEvent, sizeof(struct input_event));

        if (bytesRead == sizeof(struct input_event)) {
            // EV_KEY 이벤트가 발생했는지 확인(키 누름 or 뗌)
            if (stEvent.type == EV_KEY) {
                // 키가 눌렸는지 확인 (버튼 누름)
                if (stEvent.value == 1) {
                    // 버튼 누름 확인, 메시지 보내기
                    struct msgbuf message;
                    message.mtype = 1;
                    message.mtext = "Button Pressed";   //메시지 내용
                    msgsnd(msgID, &message, sizeof(struct msgbuf), 0);
                }
            }
        }
    
}
