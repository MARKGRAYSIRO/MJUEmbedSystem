#include <pthread.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "fnd.h"
#include "accelMagGyro.h"
#include "buzzer.h"
#include "led.h"
#include "screen.h"
#include "touch.h"
#include "jpgAnimation.h"

//쓰레드 id 정의
pthread_t start_read_jpgTH_ID; //f or jpeg files
static pthread_t start_on_offTH_ID;   // for Q1 start
static pthread_t game1_startTH_ID;    // for game1 start touch
static pthread_t game1_endTH_ID;      // for game1 end   touch
static pthread_t touchTH_ID1;         // for start touch
static pthread_t touchTH_ID2;         // for skip next Question
static pthread_t bmpTH_ID_1;          // frist  Question image
static pthread_t bmpTH_ID_2;          // second Question image
static pthread_t buzzercountdownTH_ID;
static pthread_t ledCountdownTH_ID;
static pthread_t fndCountdownTH_ID;

//사용할 전역변수 정의
static int G=0,S=0,H=0,R=0;
static int leave_Q =5; 
static int start_on_off =1;
static int counterdownnum =0;

//쓰레드 선언부
void* read_jpg_start(void*arg);
static void* start_on_onTHFunc(void*arg);
static void* game1_startTHFunc(void*arg);
static void* game1_endTHFunc(void*arg)l;
static void* touchTHFunc1(void* arg);
static void* touchTHFunc2(void* arg);
static void* bmpTHFunc1(void* arg);
static void* bmpTHFunc2(void* arg);
static void* buzzercountdownTHFunc(void*arg);
static void* ledcountdownTHFunc(void*arg);
static void* fndCountdownTHFunc(void*arg);

//쓰래드 구현부
void* start_on_onTHFunc(void*arg){
    while(start_on_off){
        bmp_read("./start_on_off/start_off.bmp");
        usleep(500000);
        bmp_read("./start_on_off/start_on.bmp");
        usleep(500000);
    }
    pthread_exit(NULL);
}

void* game1_startTHFunc(void*arg){
    whlie(start_on_off){ usleep(100); }
    //bmp_read(); game1 설명 bmp 파일 넣기
    phtread_exit(NULL);
}

void* game1_endTHFunc(void*arg){
    //bmp_read(); 게임 끝 touch 이미지 띄우기
    while(start_on_off){ usleep(100); }
    
}

void* touchTHFunc1(void* arg){
    touchInit();

    int msgID1 = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    BUTTON_MSG_T recvMsg1;
        while(1){
        msgrcv(msgID1, &recvMsg1, sizeof(recvMsg1) - sizeof(long int), 0, 0);

        if (recvMsg1.keyInput == 999 && recvMsg1.pressed == 1) start_on_off = 0;
        }
    
}

void* touchTHFunc2(void* arg){
    touchInit();

    int msgID2 = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    BUTTON_MSG_T recvMsg2;
    while (1) {
        msgrcv(msgID2, &recvMsg2, sizeof(recvMsg2) - sizeof(long int), 0, 0);
        if (recvMsg2.keyInput == 999 && recvMsg2.pressed == 1) {
            if (recvMsg2.x >= 267 && recvMsg2.x <=400 && recvMsg2.y >= 26 && recvMsg2.y <=574) {            
               G++; leave_Q--;
            }
            else if (recvMsg2.x > 458 && recvMsg2.x <= 593 && recvMsg2.y >= 26 && recvMsg2.y <=574) {
               S++; leave_Q--;
            }
            else if (recvMsg2.x > 650 && recvMsg2.x <= 785 && recvMsg2.y >= 26 && recvMsg2.y <=574) {
               R++; leave_Q--;
            }
            else if (recvMsg2.x > 843 && recvMsg2.x <= 980 && recvMsg2.y >= 26 && recvMsg2.y <=574) {
               H++; leave_Q--;
            }
            else ;
        }
        }
    
}

void* bmpTHFunc1(void* arg){
    int lastLeave_Q = 6;
    while(1){
        usleep(100000);
        if (leave_Q != lastLeave_Q) {
            switch(leave_Q){
                case 5: {bmp_read("./Q1image/Q1.bmp"); lastLeave_Q = leave_Q; usleep(1000); break;}
                case 4: bmp_read("./Q1image/Q2.bmp"); break;
                case 3: bmp_read("./Q1image/Q3.bmp"); break;
                case 2: bmp_read("./Q1image/Q4.bmp"); break;
                case 1: bmp_read("./Q1image/Q5.bmp"); break;
                case 0: bmp_read("./gameimage/game1_start.bmp"); break;
            }
            lastLeave_Q = leave_Q;
        }
    }
}

void* bmpTHFunc2(void* arg){
    int lastLeave_Q = 6;
    while(1){
        usleep(100000);
        if (leave_Q != lastLeave_Q) {
            switch(leave_Q){
                case 5: {bmp_read("./Q1image/Q6.bmp"); lastLeave_Q = leave_Q; usleep(1000); break;}
                case 4: bmp_read("./Q1image/Q7.bmp"); break;
                case 3: bmp_read("./Q1image/Q8.bmp"); break;
                case 2: bmp_read("./Q1image/Q9.bmp"); break;
                case 1: bmp_read("./Q1image/Q10.bmp"); break;
                case 0: bmp_read("./gameimage/game2_start.bmp"); break;
            }
            lastLeave_Q = leave_Q;
        }
    }
}

void* buzzercountdownTHFunc(void *arg){
     buzzerCountdown(counterdownnum);
     pthread_exit(NULL);
}

void* ledcountdownTHFunc(void *arg){
     ledCountdown(counterdownnum);
     pthread_exit(NULL);
}

void* fndcountdownTHFunc(void *arg){
     fndCountdown(counterdownnum);
     pthread_exit(NULL);
}

//최종실행파일 선언부
static void start(void);
static void Question_1(void);
static void game1(void);
static void Question_2(void);


//최종실행파일 구현부
void start(void){
    
    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);

    pthread_create(&start_on_offTH_ID, NULL, start_on_onTHFunc, NULL);
    pthread_join(start_on_offTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);

    pthread_create(&start_read_jpgTH_ID, NULL, read_jpg_start, NULL);
    pthread_join(start_read_jpgTH_ID, NULL);
    sleep(1);
}

void Question_1(void){

    leave_Q = 5; 

    pthread_create(&touchTH_ID2, NULL, touchTHFunc2, NULL);
    pthread_detach(touchTH_ID2);

    pthread_create(&bmpTH_ID_1, NULL, bmpTHFunc1, NULL);
    pthread_detach(bmpTH_ID_1);

    while(leave_Q != 0){ sleep(2);}
       touchExit();
    sleep(1);
    pthread_cancel(touchTH_ID2);
    pthread_cancel(bmpTH_ID_1);

 
}

void game1(void){   
    start_on_off = 1;
    counterdownnum = 5;
    int mag[3];
    float temp;

    float magSum = 0;
    float tempSum = 0;

    // 화면 터치되면 다음 설명으로 넘어가기.
    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);
    pthread_create(&game1_startTH_ID, NULL, game1_startTHFunc, NULL);
    pthread_join(game1_startTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);

    //5초 세기 카운터 다운
    fndCountdown(5);
    bmp_read("./gameimage/game1_ing.bmp");
    //fnd counterdown 5초 생성하기.
    
    pthread_create(&buzzercountdownTH_ID, NULL, buzzercountdownTHFunc, NULL);
    pthread_detach(buzzercountdownTH_ID, NULL);
    pthread_create(&ledCountdownTH_ID, NULL, ledcountdownTHFunc, NULL);
    pthread_detach(ledCountdownTH_ID, NULL);
    sleep(5);

    //5초 후 값 받아 드리기
    getMag(mag);
    temp = getTemp();

    mag[0] = (mag[0]>0)? mag[0]: -mag[0];
    mag[1] = (mag[1]>0)? mag[1]: -mag[1];
    mag[2] = (mag[2]>0)? mag[2]: -mag[2];

    magSum = mag[0] + mag[1] + mag[2];
    tempSum = temp - (int)temp;

    // index 증가
    if     (magSum <5000)                     F = F + 3;
    else if(magSum >= 5000 && magSum < 10000) R = R + 3;
    else if(magSum >= 10000 && magSum < 20000)G = G + 3;
    else                                      S = S + 3;

    if     (tempSum < 24.0)                  S = S + 3;
    else if(tempSum>= 24.0 && tempSum < 25.5)G = G + 3;
    else if(tempSum>= 25.5 && tempSum < 27.0)R = R + 3;
    else                                     F = F + 3;


    start_on_off = 1;
    usleep(100);


    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);
    pthread_create(&game1_endTH_ID, NULL, game1_endTHFunc, NULL);
    pthread_join(game1_endTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);
}

void Question_2(void){

    leave_Q = 5; 

    pthread_create(&touchTH_ID2, NULL, touchTHFunc2, NULL);
    pthread_detach(touchTH_ID2);

    pthread_create(&bmpTH_ID_2, NULL, bmpTHFunc2, NULL);
    pthread_detach(bmpTH_ID_2);

    while(leave_Q != 0){ usleep(100000);}
       touchExit();
    sleep(1);
    pthread_cancel(touchTH_ID2);
    pthread_cancel(bmpTH_ID_2);
}



int main(void){
    start();

    Question_1();
    
    game1();

    Question_2();
    printf("%d, %d, %d, %d", G, S, R, H);
    return 0;
}