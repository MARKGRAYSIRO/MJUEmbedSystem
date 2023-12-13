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

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd evnet"

static int fp;
static int readSize, inputIndex;
static struct input_event stEvent;
static char buttonPath[200]={0,};
static int exit_pth=0; //exit signal for thread
static pthread_t buttonTh_id;
static int msgID;
BUTTON_MSG_T send;

// 버튼 경로를 탐색하는 함수
int probeButtonPath(char *newPath){
    int returnValue = 0; // 반환값을 위한 변수
    int number = 0; // 디바이스 번호를 저장할 변수
    FILE* fp = fopen(PROBE_FILE, "rt"); // /proc/bus/input/devices 파일을 읽기 모드로 열기
    while(!feof(fp)){ // 파일의 끝에 도달할 때까지 반복
        char tmpStr[200]; // 임시 문자열 저장을 위한 배열
        fgets(tmpStr, 200, fp); // 한 줄 읽기
        if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0){ // 첫 번째 키워드가 있는지 확인
            printf("YES! I found!: %s\r\n", tmpStr); // 찾았다고 출력
            returnValue = 1; // 찾았음을 표시
        }
        if ((returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0)){ // 두 번째 키워드 확인
            printf ("-->%s", tmpStr); // 찾았다고 출력
            printf("\t%c\r\n", tmpStr[strlen(tmpStr)-3]); // 관련 문자 출력
            number = tmpStr[strlen(tmpStr)-3] - '0'; // 숫자로 변환
            break; // 반복문 탈출
        }
    }
    fclose(fp); // 파일 닫기
    if (returnValue == 1)
    sprintf (newPath,"%s%d", INPUT_DEVICE_LIST, number); // 찾은 경로를 newPath에 저장
    return returnValue; // 결과 반환
}

// 버튼 초기화 함수
int buttonInit(void)
{
    if (probeButtonPath(buttonPath) == 0 ) // 버튼 경로를 찾는데 실패하면
        return 0; // 0 반환
    msgID = msgget (MESSAGE_ID, IPC_CREAT|0666); // 메시지 큐 생성 또는 접근
    fp = open (buttonPath, O_RDONLY); // 버튼 디바이스 파일 열기
    pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL); // 쓰레드 생성
    int a = pthread_detach (buttonTh_id); // 쓰레드 분리
    if (a != 0){ // 분리에 실패하면
        printf("error of detaching thread\r\n"); // 에러 메시지 출력
    }
    return 1; // 성공적으로 초기화됨
}

// 버튼 쓰레드 함수
void* buttonThFunc(void *arg){
    while(1){ // 무한 루프
        send.messageNum = 1; // 메시지 번호 설정
        readSize = read(fp, &stEvent, sizeof(stEvent)); // 이벤트 읽기
        
        if (readSize != sizeof(stEvent)){ // 정상적으로 읽지 못하면
            continue; // 다시 시도
        }

        if (exit_pth == 1){ // 종료 신호가 있으면
            pthread_exit(NULL); // 쓰레드 종료
        }

        if (stEvent.type == EV_KEY){
            // 키에 따른 처리
            switch(stEvent.code){
                case KEY_VOLUMEUP:
                    send.keyInput = 1;
                    msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
                    break;
                
                case KEY_HOME:
                    send.keyInput = 2;
                    msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
                    break;

                case KEY_SEARCH:
                    send.keyInput = 3;
                    msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
                    break;

                case KEY_BACK:
                    send.keyInput = 4;
                    msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
                    break;

                case KEY_MENU:
                    send.keyInput = 5;
                    msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
                    break;

                case KEY_VOLUMEDOWN:
                    send.keyInput = 6;
                    msgsnd(msgID, &send.keyInput, sizeof(send.keyInput), 0);
                    break;
            }
            // 버튼 눌림/떨어짐 상태에 따른 처리
            if (stEvent.value){
                send.pressed = 1;
                msgsnd(msgID, &send.pressed, sizeof(send.pressed), 0);
            }

            else {
                send.pressed = 3;
                msgsnd(msgID, &send.pressed, sizeof(send.pressed), 0);
                printf("\n");
            }
        }
        else //EV_SYN
        ; // do notthing
    }
    close(fp);
}

int buttonExit(void){
    exit_pth = 1; // 종료 신호 설정
    close(fp); // 종료
}
