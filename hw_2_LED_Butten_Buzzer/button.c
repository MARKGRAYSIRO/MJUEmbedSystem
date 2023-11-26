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

/*while(1){

    (쓰레드 작성)
    input device node에 대해 read 한다. blocking mode
    read에 성공하면 = (버튼이 눌렸다.) stEvent를 messend 해준다.
}
*/
