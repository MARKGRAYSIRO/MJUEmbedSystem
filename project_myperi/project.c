#include <pthread.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>

#include "screen.h"
#include "touch.h"


//최종실행파일
static void Question_1(void);
static void Question_2(void);


//쓰레드 id 정의
static pthread_t touchTH_ID;
static pthread_t bmpTH_ID_1;
static pthread_t bmpTH_ID_2;


//쓰레드 함수 정의
static void* touchTHFunc(void* arg);
static void* bmpTHFunc1(void* arg);
static void* bmpTHFunc2(void* arg);


//사용할 전역변수 정의
static int G=0,S=0,H=0,R=0;
static int leave_Q =5; 




void* touchTHFunc(void* arg){
    touchInit();

    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    BUTTON_MSG_T recvMsg;
    while (1) {
        msgrcv(msgID, &recvMsg, sizeof(recvMsg) - sizeof(long int), 0, 0);
        if (recvMsg.keyInput == 999 && recvMsg.pressed == 1) {
            if (recvMsg.x >= 267 && recvMsg.x <=400 && recvMsg.y >= 26 && recvMsg.y <=574) {            
               G++; leave_Q--;
            }
            else if (recvMsg.x > 458 && recvMsg.x <= 593 && recvMsg.y >= 26 && recvMsg.y <=574) {
               S++; leave_Q--;
            }
            else if (recvMsg.x > 650 && recvMsg.x <= 785 && recvMsg.y >= 26 && recvMsg.y <=574) {
               R++; leave_Q--;
            }
            else if (recvMsg.x > 843 && recvMsg.x <= 980 && recvMsg.y >= 26 && recvMsg.y <=574) {
               H++; leave_Q--;
            }
            else ;
        }
        }
    
}

void* bmpTHFunc1(void* arg){
    int lastLeave_Q = 5;
    while(1){
        usleep(100000);
        if (leave_Q != lastLeave_Q) {
            switch(leave_Q){
                case 5: {bmp_read("./Q1image/Q1.bmp"); lastLeave_Q = leave_Q; usleep(1000); break;}
                case 4: bmp_read("./Q1image/Q2.bmp"); break;
                case 3: bmp_read("./Q1image/Q3.bmp"); break;
                case 2: bmp_read("./Q1image/Q4.bmp"); break;
                case 1: bmp_read("./Q1image/Q5.bmp"); break;
                case 0: bmp_read("./Q1image/Q5.bmp"); break;
            }
            lastLeave_Q = leave_Q;
        }
    }
}

void* bmpTHFunc2(void* arg){
    int lastLeave_Q = 5;
    while(1){
        usleep(100000);
        if (leave_Q != lastLeave_Q) {
            switch(leave_Q){
                case 5: {bmp_read("./Q1image/Q6.bmp"); lastLeave_Q - leave_Q; usleep(1000); break;}
                case 4: bmp_read("./Q1image/Q7.bmp"); break;
                case 3: bmp_read("./Q1image/Q8.bmp"); break;
                case 2: bmp_read("./Q1image/Q9.bmp"); break;
                case 1: bmp_read("./Q1image/Q10.bmp"); break;
                case 0: bmp_read("./Q1image/Q10.bmp"); break;
            }
            lastLeave_Q = leave_Q;
        }
    }
}


//마지막에 touchExit 해주기.
void Question_1(void){

    leave_Q = 5; 

    pthread_create(&touchTH_ID, NULL, touchTHFunc, NULL);
    pthread_detach(touchTH_ID);

    pthread_create(&bmpTH_ID_1, NULL, bmpTHFunc1, NULL);
    pthread_detach(bmpTH_ID_1);

    while(leave_Q != 0){ sleep(1);}
       touchExit();
    sleep(1);
    pthread_cancel(touchTH_ID);
    pthread_cancel(bmpTH_ID_1);

 
}

void Question_2(void){

    leave_Q = 5; 

    pthread_create(&touchTH_ID, NULL, touchTHFunc, NULL);
    pthread_detach(touchTH_ID);

    pthread_create(&bmpTH_ID_2, NULL, bmpTHFunc2, NULL);
    pthread_detach(bmpTH_ID_2);

    while(leave_Q != 0){ usleep(100000);}
       touchExit();
    sleep(1);
    pthread_cancel(touchTH_ID);
    pthread_cancel(bmpTH_ID_2);

    
}



int main(void){


    Question_1();

    Question_2();
    printf("%d, %d, %d, %d", G, S, H, R);
    return 0;
}