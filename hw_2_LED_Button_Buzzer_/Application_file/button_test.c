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
#include "led.h"

int main(void){
    BUTTON_MSG_T rcv; // 버튼 메시지 구조체
    int msgID = msgget(MESSAGE_ID, IPC_CREAT|0666); // 메시지 큐 생성 또는 접근

    buttonInit(); // 버튼 초기화

    while(1){ // 무한 루프
        // 키 입력 메시지 수신
        msgrcv(msgID, &rcv.keyInput, sizeof(rcv.keyInput), 0, 0);
        switch(rcv.keyInput){ // 키 입력에 따른 처리
            case(1): printf("VOLUMEUP\r\n");
                break;
            case(2): printf("HOME\r\n");
                break;
            case(3): printf("SEARCH\r\n");
                break;
            case(4): printf("BACK\r\n");
                break;
            case(5): printf("MENU\r\n");
                break;
            case(6): printf("VOLUMEDOWN\r\n");
                break;
        }
        // 버튼 상태 메시지 수신
        msgrcv(msgID, &rcv.pressed, sizeof(rcv.pressed), 0, 0);
        switch(rcv.pressed){ // 버튼 상태에 따른 처리
            case(1): printf("on\r\n");
                break;
            case(3): printf("off\r\n");
                break;
        }
    }
    buttonExit();
}