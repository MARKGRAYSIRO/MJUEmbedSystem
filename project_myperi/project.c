#include <pthread.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "temperature.h"
#include "fnd.h"
#include "accelMagGyro.h"
#include "buzzer.h"
#include "led.h"
#include "screen.h"
#include "touch.h"
#include "jpgAnimation.h"

//쓰레드 id 정의
pthread_t start_read_jpgTH_ID; //f or jpeg files
static pthread_t music1TH_ID;
static pthread_t start_on_offTH_ID;   // for Q1 start
static pthread_t game1_startTH_ID;    // for game1 start touch
static pthread_t game1_endTH_ID;      // for game1 end   touch
static pthread_t game2_startTH_ID;    // for game2 start touch
static pthread_t game2_endTH_ID;      // for game2 end   touch
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
static int tmp=0;

//쓰레드 선언부
void* read_jpg_start(void*arg);
static void* music1THFunc(void*arg);
static void* start_on_onTHFunc(void*arg);
static void* game1_startTHFunc(void*arg);
static void* game1_endTHFunc(void*arg);
static void* game2_startTHFunc(void*arg);
static void* game2_endTHFunc(void*arg);
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

void* music1THFunc(void* arg){
    while(1){
     buzzerInit();
    
    buzzerPlaySong(1);
    beat(1);
    
    buzzerPlaySong(6);
    beat(1.5);
    buzzerPlaySong(9);
    beat(0.5);
    buzzerPlaySong(8);
    beat(1);
    
    buzzerPlaySong(6);
    beat(2);
    buzzerPlaySong(13);
    beat(1);
    
    buzzerPlaySong(11);
    beat(3);
    
    buzzerPlaySong(8);
    beat(3);
    
    //2마디
    buzzerPlaySong(6);
    beat(1.5);
    buzzerPlaySong(9);
    beat(0.5);
    buzzerPlaySong(8);
    beat(1);
    
    buzzerPlaySong(5);
    beat(2);
    buzzerPlaySong(8);
    beat(1);
    
    buzzerPlaySong(1);
    beat(5);
    buzzerPlaySong(1);
    beat(1);
    
    //3마디
    buzzerPlaySong(6);
    beat(1.5);
    buzzerPlaySong(9);
    beat(0.5);
    buzzerPlaySong(8);
    beat(1);
    
    buzzerPlaySong(6);
    beat(2);
    buzzerPlaySong(13);
    beat(1);
    
    buzzerPlaySong(16);
    beat(2);
    buzzerPlaySong(15);
    beat(1);
    
    buzzerPlaySong(14);
    beat(2);
    buzzerPlaySong(10);
    beat(1);
    
     //4마디
    buzzerPlaySong(14);
    beat(1.5);
    buzzerPlaySong(13);
    beat(0.5);
    buzzerPlaySong(12);
    beat(1);
    
    buzzerPlaySong(18);
    beat(2);
    buzzerPlaySong(9);
    beat(1);
    
    buzzerPlaySong(6);
    beat(3);
    
    buzzerPlaySong(6);
    beat(2);
    buzzerPlaySong(9);
    beat(1);
    
    //5마디
    buzzerPlaySong(13);
    beat(2);
    buzzerPlaySong(9);
    beat(1);
    
    buzzerPlaySong(13);
    beat(2);
    buzzerPlaySong(9);
    beat(1);
    
    buzzerPlaySong(14);
    beat(2);
    buzzerPlaySong(13);
    beat(1);
    
    buzzerPlaySong(12);
    beat(2);
    buzzerPlaySong(8);
    beat(1);
    
    //6마디
    buzzerPlaySong(9);
    beat(1.5);
    buzzerPlaySong(13);
    beat(0.5);
    buzzerPlaySong(12);
    beat(1);
    
    buzzerPlaySong(18);
    beat(2);
    buzzerPlaySong(1);
    beat(1);
    
    buzzerPlaySong(13);
    beat(5);
    buzzerPlaySong(9);
    beat(1);
    
    //7마디
    buzzerPlaySong(13);
    beat(2);
    buzzerPlaySong(9);
    beat(1);
    
    buzzerPlaySong(13);
    beat(2);
    buzzerPlaySong(9);
    beat(1);
    
    buzzerPlaySong(16);
    beat(2);
    buzzerPlaySong(15);
    beat(1);
    
    buzzerPlaySong(14);
    beat(2);
    buzzerPlaySong(10);
    beat(1);
    
    //8마디
    buzzerPlaySong(14);
    beat(1.5);
    buzzerPlaySong(13);
    beat(0.5);
    buzzerPlaySong(12);
    beat(1);
    
    buzzerPlaySong(18);
    beat(2);
    buzzerPlaySong(9);
    beat(1);
    
    buzzerPlaySong(6);
    beat(6);

    sleep(3);
    }
}

void* game1_startTHFunc(void*arg){
    while(start_on_off){ usleep(100); }
    bmp_read("./gameimage/game1_manu.bmp");
    //bmp_read(); game1 설명 bmp 파일 넣기
    pthread_exit(NULL);
}

void* game1_endTHFunc(void*arg){
    //bmp_read(); 게임 끝 touch 이미지 띄우기
    bmp_read("./gameimage/game1_done.bmp");
    while(start_on_off){ usleep(100); }
    
}

void* game2_startTHFunc(void*arg){
    while(start_on_off){ usleep(100); }
    bmp_read("./gameimage/game2_manu.bmp"); 
    //bmp_read(); game2 설명 bmp 파일 넣기
    pthread_exit(NULL);
}

void* game2_endTHFunc(void*arg){
    int tmpindex[4];
    tmpindex[0] = S;
    tmpindex[1] = G;
    tmpindex[2] = R;
    tmpindex[3] = H;
    int i=0;
    char resultfilename[50];
    tmp = S;

    for(i=1; i<4; i++){
        if(tmp>tmpindex[i])tmp = tmpindex[i];
    }

    while(start_on_off){ usleep(1000); }


    if(tmp==S)     snprintf(resultfilename,50,"./resultimage/S.bmp");
    else if(tmp==G)snprintf(resultfilename,50,"./resultimage/G.bmp");
    else if(tmp==R)snprintf(resultfilename,50,"./resultimage/R.bmp");
    else if(tmp==H)snprintf(resultfilename,50,"./resultimage/H.bmp");
       
    bmp_read(resultfilename); // 결과 이미지 뛰우기

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
static void game2(void);


//최종실행파일 구현부
void start(void){
    
    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);

    pthread_create(&start_on_offTH_ID, NULL, start_on_onTHFunc, NULL);
    pthread_join(start_on_offTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);

    pthread_create(&music1TH_ID, NULL, music1THFunc, NULL);
    pthread_detach(music1TH_ID);

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

    while(leave_Q != 0){ usleep(100000);}
       touchExit();
    sleep(1);
    pthread_cancel(touchTH_ID2);
    pthread_cancel(bmpTH_ID_1);

    buzzerStopSong();
    pthread_cancel(music1TH_ID);
    pthread_cancel(music1TH_ID);

 
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
    fndCountdown(10);
    bmp_read("./gameimage/game1_ing.bmp");
    //fnd counterdown 5초 생성하기.
    
    pthread_create(&buzzercountdownTH_ID, NULL, buzzercountdownTHFunc, NULL);
    pthread_detach(buzzercountdownTH_ID);
    pthread_create(&ledCountdownTH_ID, NULL, ledcountdownTHFunc, NULL);
    pthread_detach(ledCountdownTH_ID);
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
    if     (magSum <5000)                     H = H + 3;
    else if(magSum >= 5000 && magSum < 10000) R = R + 3;
    else if(magSum >= 10000 && magSum < 20000)G = G + 3;
    else                                      S = S + 3;

    if     (tempSum < 24.0)                  S = S + 3;
    else if(tempSum>= 24.0 && tempSum < 25.5)G = G + 3;
    else if(tempSum>= 25.5 && tempSum < 27.0)R = R + 3;
    else                                     H = H + 3;


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
    pthread_create(&music1TH_ID, NULL, music1THFunc, NULL);
    pthread_detach(music1TH_ID);
    
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

void game2(void){
    //s <- G <- H <- R
    int numIterations = 40;    //iteration     (     Ƚ  )
    int totalTime = 20;         //      ð      
    int delay = totalTime * 1000000 / numIterations;
    int i;
    char filename[50];
    int gyro[3]= {0,0,0};
    int area = 0;
    int broomscore = 0;
    int x = 0;
    int y = 0;
    double angle;
    double result;
    
    start_on_off = 1;
    usleep(100);
    // 화면 터치되면 다음 게임설명으로 넘어가기.
    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);
    pthread_create(&game2_startTH_ID, NULL, game2_startTHFunc, NULL);
    pthread_join(game2_startTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);


        buzzerStopSong();
    pthread_cancel(music1TH_ID);
    

    //센즈 읍악

    //빗자루 설명
    fndCountdown(10);
    bmp_read("./groomimage/broom_0.bmp");

    // Loop through each set of coordinates
    for(i = 0; i < numIterations; i++){

        getAccel(gyro);
        usleep(10);

        // Extract x and y values from gyroscope data
        x = gyro[0];
        y = gyro[1];


        
        result = custom_atan2(y, x);
    
        angle = to_degrees(result);
    
        
        
        // Define the position on the Cartesian system
        // Divide area by degrees (15 degrees per area)

        printf("Angle: %f\n", angle);

        if (x > -1000 && x < 1000 && y > -1000 && y < 1000) {
            area = 0;  bmp_read(".groomimage/broom_0.bmp");        
        }
        else{
            if (0 <= angle && angle < 15) {
                area = 1;
                ++broomscore; bmp_read(".groomimage/broom_1.bmp");
            }
            else if (15 <= angle && angle < 30) {
                area = 2;
                ++broomscore; bmp_read(".groomimage/broom_2.bmp");
            }
            else if (30 <= angle && angle < 45) {
                area = 3;
                ++broomscore; bmp_read(".groomimage/broom_3.bmp");
            }
            else if (45 <= angle && angle < 60) {
                area = 4;
                ++broomscore; bmp_read(".groomimage/broom_4.bmp");
            }
            else if (60 <= angle && angle < 75) {
                area = 5;
                ++broomscore; bmp_read(".groomimage/broom_5.bmp");
            }
            else if (75 <= angle && angle < 90) {
                area = 6;
                ++broomscore;
            }
            else if (90 <= angle && angle < 105) {
                area = 7;
                ++broomscore;
            }
            else if (105 <= angle && angle < 120) {
                area = 8;
                ++broomscore;
            }
            else if (120 <= angle && angle < 135) {
                area = 9;
                ++broomscore;
            }
            else if (135 <= angle && angle < 150) {
                area = 10;
                ++broomscore;
            }
            else if (150 <= angle && angle < 165) {
                area = 11;
                ++broomscore;
            }
            else if (165 <= angle && angle < 180) {
                area = 12;
                ++broomscore;
            }
            else if (180 <= angle && angle < 195) {
                area = 13;
                ++broomscore;
            }
            else if (195 <= angle && angle < 210) {
                area = 14;
                ++broomscore;
            }
            else if (210 <= angle && angle < 225) {
                area = 15;
                ++broomscore;
            }
            else if (225 <= angle && angle < 240) {
                area = 16;
                ++broomscore;
            }
            else if (240 <= angle && angle < 255) {
                area = 17;
                ++broomscore;
            }
            else if (255 <= angle && angle < 270) {
                area = 18;
                ++broomscore;
            }
            else if (270 <= angle && angle < 285) {
                area = 19;
                ++broomscore;
            }
            else if (285 <= angle && angle < 300) {
                area = 20;
                ++broomscore;
            }
            else if (300 <= angle && angle < 315) {
                area = 21;
                ++broomscore;
            }
            else if (315 <= angle && angle < 330) {
                area = 22;
                ++broomscore;
            }
            else if (330 <= angle && angle < 345) {
                area = 23;
                ++broomscore;
            }
            else if (345 <= angle && angle <= 360) {
                area = 24;
                ++broomscore;
            }
        }

        printf("Area : %d\n", area);
        snprintf(filename,50,"./groomimage/broom_%d.bmp",area);
        bmp_read(filename);
        usleep(delay);
    }

    sleep(1);
    // Game ended. Printing result
    printf("\n\nScore : %d\n", broomscore);
    // index updates
    if(0 <= broomscore && broomscore < 10){S = S + 6;}
    else if(10 <= broomscore && broomscore < 20){G = G + 6;}
    else if(20 <= broomscore && broomscore < 30){H = H + 6;}
    else if(30 <= broomscore && broomscore <= 40){R = R + 6;}
    else printf("Score calculating error!");

    bmp_read("./gameimage/game2_done.bmp");

    start_on_off = 1;
    usleep(1000);
    // 화면 터치되면 다음 결과화면으로 넘어가기.
    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);
    pthread_create(&game2_endTH_ID, NULL, game2_endTHFunc, NULL);
    pthread_join(game2_endTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);

}

void result(void){
    sleep(5);
    char QRfilename[50];


    if(tmp==S)     snprintf(QRfilename,50,"./QRimage/QRS.bmp");
    else if(tmp==G)snprintf(QRfilename,50, "./QRimage/QRG.bmp");
    else if(tmp==R)snprintf(QRfilename,50, "./QRimage/QRR.bmp");
    else if(tmp==H)snprintf(QRfilename,50, "./QRimage/QRH.bmp");
    //bmp_read(QRfilename);   
}


int main(void){
    //start();

    //Question_1();
    
    //game1();

    Question_2();

    game2();

   // result();

    printf("%d, %d, %d, %d", G, S, R, H);
    return 0;
}