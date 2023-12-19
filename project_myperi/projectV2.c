#include <pthread.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>

#include "temperature.h"
#include "accelMagGyro.h"
#include "screen.h"
#include "touch.h"


//최종실행파일
static void Question_1(void);
static void Question_2(void);
static void Minigame_1(void);
static void Minigame_2(void);

//쓰레드 id 정의
static pthread_t touchTH_ID;
static pthread_t touchTH_ID_2;
static pthread_t bmpTH_ID_1;
static pthread_t bmpTH_ID_2;
static pthread_t bmpTH_ID_3;
static pthread_t bmpTH_ID_4;

//쓰레드 함수 정의
static void* touchTHFunc(void* arg);
static void* bmpTHFunc1(void* arg);
static void* bmpTHFunc2(void* arg);
static void* bmpTHFunc3(void* arg);
static void* bmpTHFunc4(void* arg);

//사용할 전역변수 정의
static int G=0,S=0,H=0,R=0;
static int leave_Q =5; 
static int touchCount = 0; //touch event counter for Minigame1
static float globalTempMax = 0.0f; // Global variable to store tempMax
static float globalMagMaxSum = 0.0f; // Global variable to store magMaxSum
static float globalGyroDiff = 0.0f; // Global variable to store the difference



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

void* touchTHFunc2(void* arg){ //touchFunc for Minigame1
    touchInit();
    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    BUTTON_MSG_T recvMsg;
    while (1) {
        msgrcv(msgID, &recvMsg, sizeof(recvMsg) - sizeof(long int), 0, 0);
        if (recvMsg.keyInput == 999 && recvMsg.pressed == 1) {
            touchCount++; // 터치 이벤트 발생 시 touchCount 증가
            if (touchCount >= 2) {
                break; // 두 번째 터치 후 반복문 탈출
            }
        }
    }

    touchExit();
    return NULL;
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

extern int touchCount; // 외부에서 선언된 touchCount 사용

void* bmpTHFunc3(void* arg) { // 미니게임1 이미지
    while (1) {
        usleep(100000); // 0.1초 대기
        if (touchCount == 1) {
            bmp_read("./Q1image/Q1.bmp"); // 게임 시작 이미지, 추후 변경 필요
        } else if (touchCount == 2) {
            bmp_read("./Q1image/Q1.bmp"); // 게임 안내 이미지, 추후 변경 필요
            break; // 두 번째 터치 후 반복문 탈출
        }
    }
    return NULL;
}

void* bmpTHFunc4(void* arg) { // 미니게임2 이미지
    while (1) {
        usleep(100000); // 0.1초 대기
        if (touchCount == 1) {
            bmp_read("./Q1image/Q1.bmp"); // 게임 시작 이미지, 추후 변경 필요
        } else if (touchCount == 2) {
            bmp_read("./Q1image/Q1.bmp"); // 게임 안내 이미지, 추후 변경 필요
            break; // 두 번째 터치 후 반복문 탈출
        }
    }
    return NULL;
}

void Minigame_1(void) {
    float magMaxSum = 0.0f;
    float tempMax = 0.0f;

    for (int i = 0; i < 50; i++) {
        int mag[3];
        float temp;

        getMag(mag);
        temp = getTemp();

        float magSum = fabs(mag[0]) + fabs(mag[1]) + fabs(mag[2]);
        magMaxSum = fmax(magMaxSum, magSum);

        float tempFraction = temp - (int)temp;
        tempMax = fmax(tempMax, tempFraction);

        usleep(100000); // 0.1초 대기
    }
    globalMagMaxSum = magMaxSum; //글로벌 변수에 저장해서 나중에 결과를 낼때 값을 읽을 수 있도록 함
    globalTempMax = tempMax;
    printf("Magnetometer Max Sum: %.3f\n", magMaxSum);
    printf("Temperature Fraction Max: %.3f\n", tempMax);
}

void Minigame_2(void) {
    float gyroMax = -3000.0f;
    float gyroMin = 3000.0f;
    float gyroData[3];

    for (int i = 0; i < 50; i++) {
        processGyroData(gyroData);

        for (int j = 0; j < 2; j++) { // x, y 데이터만 읽음
            gyroMax = fmax(gyroMax, gyroData[j]);
            gyroMin = fmin(gyroMin, gyroData[j]);
        }

        usleep(100000); // 0.1초 대기
    }

    globalGyroDiff = gyroMax - gyroMin; // 자이로 맥스값과 미니멈값을 저장함.
}

void startMinigame_1(void) {
    pthread_t touchTH_ID_2, bmpTH_ID_3;
    pthread_create(&touchTH_ID_2, NULL, touchTHFunc2, NULL);
    pthread_create(&bmpTH_ID_3, NULL, bmpTHFunc3, NULL);

    while (touchCount < 2) {
        usleep(100000); // 0.1초 대기
    }

    Minigame_1(); // 터치 이벤트가 2번 발생한 후에 미니게임 시작
   
    pthread_join(touchTH_ID_2, NULL); // Wait until the Minigame has successfully ended
    pthread_join(bmpTH_ID_3, NULL);
}

void processGyroData(float *gyroResult) {
    int gyro[3];
    getGyro(gyro);

    // Clamp the gyroscope data to the range [-3000, 3000]
    for (int i = 0; i < 3; i++) {
        if (gyro[i] > 3000) gyro[i] = 3000;
        else if (gyro[i] < -3000) gyro[i] = -3000;

        gyroResult[i] = gyro[i]; // Store the clamped result
    }
}

void startMinigame_2(void) {
    pthread_t touchTH_ID_2, bmpTH_ID_4; // 얘도 두번 터치하면 넘어가기때문에 touchTH_ID_2를 사용하고 이미지는 다른걸 가져와야 하므로 bmpTH_ID_4로 함
    pthread_create(&touchTH_ID_2, NULL, touchTHFunc2, NULL);
    pthread_create(&bmpTH_ID_4, NULL, bmpTHFunc4, NULL);

    while (touchCount < 2) {
        usleep(100000); // 0.1초 대기
    }

    Minigame_2(); // 터치 이벤트가 2번 발생한 후에 미니게임 시작
   
    pthread_join(touchTH_ID_2, NULL); // Wait until the Minigame has successfully ended
    pthread_join(bmpTH_ID_4, NULL);
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
    startMinigame_1();
    Question_2();
    startMinigame_2();
    printf("%d, %d, %d, %d", G, S, H, R);
    return 0;
}