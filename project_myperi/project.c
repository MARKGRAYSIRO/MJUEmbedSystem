#include <pthread.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "colorled.c"
#include "lcdtext.h"
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
static pthread_t music2TH_ID;
static pthread_t music3TH_ID;
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
static pthread_t ledTwinkleTH_ID;
static pthread_t colorledTH_ID;

//사용할 전역변수 정의
static int G=0,S=0,H=0,R=0;
static int leave_Q =5; 
static int start_on_off =1;
static int counterdownnum =0;
static int tmp=0;
static char Question[10]={'x','x','x','x','x','x','x','x','x','x'};
static int Total = 10;
static char str1[17]="x  x  x  x", str2[17]="x  x  x  x";
static int colortime = 5;

//쓰레드 선언부
void* read_jpg_start(void*arg);
static void* music1THFunc(void*arg);
static void* music2THFunc(void*arg);
static void* music3THFunc(void*arg);
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
static void* fndcountdownTHFunc(void*arg);
static void* ledTwinkleTHFunc(void*arg);
static void* colorledTHFunc(void*arg);

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
    buzzerInit();
    while(1){
    buzzerPlaySong(1);
    beat1(1);
    
    buzzerPlaySong(6);
    beat1(1.5);
    buzzerPlaySong(9);
    beat1(0.5);
    buzzerPlaySong(8);
    beat1(1);
    
    buzzerPlaySong(6);
    beat1(2);
    buzzerPlaySong(13);
    beat1(1);
    
    buzzerPlaySong(11);
    beat1(3);
    
    buzzerPlaySong(8);
    beat1(3);
    
    //2마디
    buzzerPlaySong(6);
    beat1(1.5);
    buzzerPlaySong(9);
    beat1(0.5);
    buzzerPlaySong(8);
    beat1(1);
    
    buzzerPlaySong(5);
    beat1(2);
    buzzerPlaySong(8);
    beat1(1);
    
    buzzerPlaySong(1);
    beat1(5);
    buzzerPlaySong(1);
    beat1(1);
    
    //3마디
    buzzerPlaySong(6);
    beat1(1.5);
    buzzerPlaySong(9);
    beat1(0.5);
    buzzerPlaySong(8);
    beat1(1);
    
    buzzerPlaySong(6);
    beat1(2);
    buzzerPlaySong(13);
    beat1(1);
    
    buzzerPlaySong(16);
    beat1(2);
    buzzerPlaySong(15);
    beat1(1);
    
    buzzerPlaySong(14);
    beat1(2);
    buzzerPlaySong(10);
    beat1(1);
    
     //4마디
    buzzerPlaySong(14);
    beat1(1.5);
    buzzerPlaySong(13);
    beat1(0.5);
    buzzerPlaySong(12);
    beat1(1);
    
    buzzerPlaySong(18);
    beat1(2);
    buzzerPlaySong(9);
    beat1(1);
    
    buzzerPlaySong(6);
    beat1(3);
    
    buzzerPlaySong(6);
    beat1(2);
    buzzerPlaySong(9);
    beat1(1);
    
    //5마디
    buzzerPlaySong(13);
    beat1(2);
    buzzerPlaySong(9);
    beat1(1);
    
    buzzerPlaySong(13);
    beat1(2);
    buzzerPlaySong(9);
    beat1(1);
    
    buzzerPlaySong(14);
    beat1(2);
    buzzerPlaySong(13);
    beat1(1);
    
    buzzerPlaySong(12);
    beat1(2);
    buzzerPlaySong(8);
    beat1(1);
    
    //6마디
    buzzerPlaySong(9);
    beat1(1.5);
    buzzerPlaySong(13);
    beat1(0.5);
    buzzerPlaySong(12);
    beat1(1);
    
    buzzerPlaySong(18);
    beat1(2);
    buzzerPlaySong(1);
    beat1(1);
    
    buzzerPlaySong(13);
    beat1(5);
    buzzerPlaySong(9);
    beat1(1);
    
    //7마디
    buzzerPlaySong(13);
    beat1(2);
    buzzerPlaySong(9);
    beat1(1);
    
    buzzerPlaySong(13);
    beat1(2);
    buzzerPlaySong(9);
    beat1(1);
    
    buzzerPlaySong(16);
    beat1(2);
    buzzerPlaySong(15);
    beat1(1);
    
    buzzerPlaySong(14);
    beat1(2);
    buzzerPlaySong(10);
    beat1(1);
    
    //8마디
    buzzerPlaySong(14);
    beat1(1.5);
    buzzerPlaySong(13);
    beat1(0.5);
    buzzerPlaySong(12);
    beat1(1);
    
    buzzerPlaySong(18);
    beat1(2);
    buzzerPlaySong(9);
    beat1(1);
    
    buzzerPlaySong(6);
    beat1(6);

    sleep(3);
    }
}

void* music2THFunc(void* arg){
    buzzerInit();
    
    buzzerPlaySong3(1);
    beat2(1);
    buzzerPlaySong3(2);
    beat2(1);
    buzzerPlaySong3(3);
    beat2(1.9);
    rest2(0.1);
    
    buzzerPlaySong3(4);
    beat2(0.3);
    rest2(0.03);
    buzzerPlaySong3(4);
    beat2(0.3);
    rest2(0.03);
    buzzerPlaySong3(4);
    beat2(0.3);
    rest2(0.03);
    
    buzzerPlaySong3(5);
    beat2(0.3);
    rest2(0.03);
    buzzerPlaySong3(5);
    beat2(0.3);
    rest2(0.03);
    buzzerPlaySong3(4);
    beat2(0.3);
    rest2(0.03);
    
    buzzerPlaySong3(1);
    beat2(2);
    
    buzzerStopSong();
}

void* music3THFunc(void* arg){
    buzzerInit();
    while(1){
    buzzerPlaySong2(6);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(6);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(18);
    beat3(0.4);
    rest3(0.6);
    buzzerPlaySong2(13);
    beat3(0.4);
    rest3(0.6);
    
    
    rest3(0.5);
    buzzerPlaySong2(12);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(11);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(9);
    beat3(1);
    buzzerPlaySong2(6);
    beat3(0.5);
    buzzerPlaySong2(9);
    beat3(0.5);
    buzzerPlaySong2(10);
    beat3(0.4);
    rest3(0.1);
    
    //2마디
    buzzerPlaySong2(4);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(4);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(18);
    beat3(0.4);
    rest3(0.6);
    buzzerPlaySong2(13);
    beat3(0.4);
    rest3(0.6);
    
    
    rest3(0.5);
    buzzerPlaySong2(12);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(11);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(9);
    beat3(1);
    buzzerPlaySong2(6);
    beat3(0.5);
    buzzerPlaySong2(9);
    beat3(0.5);
    buzzerPlaySong2(10);
    beat3(0.4);
    rest3(0.1);
    
    //3마디
    buzzerPlaySong2(3);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(3);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(18);
    beat3(0.4);
    rest3(0.6);
    buzzerPlaySong2(13);
    beat3(0.4);
    rest3(0.6);
    
    
    rest3(0.5);
    buzzerPlaySong2(12);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(11);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(9);
    beat3(1);
    buzzerPlaySong2(6);
    beat3(0.5);
    buzzerPlaySong2(9);
    beat3(0.5);
    buzzerPlaySong2(10);
    beat3(0.4);
    rest3(0.1);
    
    //4마디
    buzzerPlaySong2(2);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(2);
    beat3(0.4);
    rest3(0.1);
    buzzerPlaySong2(18);
    beat3(0.4);
    rest3(0.6);
    buzzerPlaySong2(13);
    beat3(0.4);
    rest3(0.6);
    
    
    rest3(0.5);
    buzzerPlaySong2(12);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(11);
    beat3(0.4);
    rest3(0.1);
    
    rest3(0.5);
    buzzerPlaySong2(9);
    beat3(1);
    buzzerPlaySong2(6);
    beat3(0.5);
    buzzerPlaySong2(9);
    beat3(0.5);
    buzzerPlaySong2(10);
    beat3(0.4);
    rest3(0.1);
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
    usleep(100);
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

        
    pwmLedInit();
    if(tmp==S)     {snprintf(resultfilename,50,"./resultimage/S.bmp");  pwmLedDorm(1);}
    else if(tmp==G){snprintf(resultfilename,50,"./resultimage/G.bmp");  pwmLedDorm(2);}
    else if(tmp==R){snprintf(resultfilename,50,"./resultimage/R.bmp");  pwmLedDorm(3);}
    else if(tmp==H){snprintf(resultfilename,50,"./resultimage/H.bmp");  pwmLedDorm(4);}

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
               switch(Total){
                case(10): Question[0] = '1';  break;
                case(9):  Question[1] = '1';  break;
                case(8):  Question[2] = '1';  break;
                case(7):  Question[3] = '1';  break;
                case(6):  Question[4] = '1';  break;
                case(5):  Question[5] = '1';  break;
                case(4):  Question[6] = '1';  break;
                case(3):  Question[7] = '1';  break;
                case(2):  Question[8] = '1';  break;
                case(1):  Question[9] = '1';  break;
               }      snprintf(str1,17,"%c  %c  %c  %c  %c",Question[0],Question[1],Question[2],Question[3],Question[4]);
                      snprintf(str2,17,"%c  %c  %c  %c  %c",Question[5],Question[6],Question[7],Question[8],Question[9]);
                      printf("str1 : %c %c %c %c %c\r\nstr2 : %c %c %c %c %c\r\n",Question[0],Question[1],Question[2],Question[3],Question[4],Question[5],Question[6],Question[7],Question[8],Question[9]);
                    usleep(10);
                    if(Total<=10 && Total>5)     lcdtextwrite(str1,"",1);
                    else if(Total<=5 && Total>0) lcdtextwrite("",str2,2);
               Total--;
            }
            else if (recvMsg2.x > 458 && recvMsg2.x <= 593 && recvMsg2.y >= 26 && recvMsg2.y <=574) {
               S++; leave_Q--;
               switch(Total){
                case(10): Question[0] = '2';  break;
                case(9):  Question[1] = '2';  break;
                case(8):  Question[2] = '2';  break;
                case(7):  Question[3] = '2';  break;
                case(6):  Question[4] = '2';  break;
                case(5):  Question[5] = '2';  break;
                case(4):  Question[6] = '2';  break;
                case(3):  Question[7] = '2';  break;
                case(2):  Question[8] = '2';  break;
                case(1):  Question[9] = '2';  break;
               }      snprintf(str1,17,"%c  %c  %c  %c  %c",Question[0],Question[1],Question[2],Question[3],Question[4]);
                      snprintf(str2,17,"%c  %c  %c  %c  %c",Question[5],Question[6],Question[7],Question[8],Question[9]);
                      printf("str1 : %c %c %c %c %c\r\nstr2 : %c %c %c %c %c\r\n",Question[0],Question[1],Question[2],Question[3],Question[4],Question[5],Question[6],Question[7],Question[8],Question[9]);
                    usleep(10);
                    if(Total<=10 && Total>5)     lcdtextwrite(str1,"",1);
                    else if(Total<=5 && Total>0) lcdtextwrite("",str2,2);
               Total--;
            }
            else if (recvMsg2.x > 650 && recvMsg2.x <= 785 && recvMsg2.y >= 26 && recvMsg2.y <=574) {
               R++; leave_Q--;
                  switch(Total){
                case(10): Question[0] = '3';  break; 
                case(9):  Question[1] = '3';  break;
                case(8):  Question[2] = '3';  break;
                case(7):  Question[3] = '3';  break;
                case(6):  Question[4] = '3';  break;
                case(5):  Question[5] = '3';  break;
                case(4):  Question[6] = '3';  break;
                case(3):  Question[7] = '3';  break;
                case(2):  Question[8] = '3';  break;
                case(1):  Question[9] = '3';  break;
               }      snprintf(str1,17,"%c  %c  %c  %c  %c",Question[0],Question[1],Question[2],Question[3],Question[4]);
                      snprintf(str2,17,"%c  %c  %c  %c  %c",Question[5],Question[6],Question[7],Question[8],Question[9]); 
                      printf("str1 : %c %c %c %c %c\r\nstr2 : %c %c %c %c %c\r\n",Question[0],Question[1],Question[2],Question[3],Question[4],Question[5],Question[6],Question[7],Question[8],Question[9]);  
                    usleep(10);
                    if(Total<=10 && Total>5)     lcdtextwrite(str1,"",1);
                    else if(Total<=5 && Total>0) lcdtextwrite("",str2,2);
               Total--;
            }
            else if (recvMsg2.x > 843 && recvMsg2.x <= 980 && recvMsg2.y >= 26 && recvMsg2.y <=574) {
               H++; leave_Q--;
                switch(Total){
                case(10): Question[0] = '4';  break;
                case(9):  Question[1] = '4';  break;
                case(8):  Question[2] = '4';  break;
                case(7):  Question[3] = '4';  break;
                case(6):  Question[4] = '4';  break;
                case(5):  Question[5] = '4';  break;
                case(4):  Question[6] = '4';  break;
                case(3):  Question[7] = '4';  break;
                case(2):  Question[8] = '4';  break;
                case(1):  Question[9] = '4';  break;
               }      snprintf(str1,17,"%c  %c  %c  %c  %c",Question[0],Question[1],Question[2],Question[3],Question[4]);
                      snprintf(str2,17,"%c  %c  %c  %c  %c",Question[5],Question[6],Question[7],Question[8],Question[9]);
                      printf("str1 : %c %c %c %c %c\r\nstr2 : %c %c %c %c %c\r\n",Question[0],Question[1],Question[2],Question[3],Question[4],Question[5],Question[6],Question[7],Question[8],Question[9]);
                    usleep(10);
                    if(Total<=10 && Total>5)     lcdtextwrite(str1,"",1);
                    else if(Total<=5 && Total>0) lcdtextwrite("",str2,2);
               Total--;
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
                case 5: {bmp_read("./Q1image/Q1.bmp"); ledTwinkle(); lastLeave_Q = leave_Q; usleep(1000); break;}
                case 4: bmp_read("./Q1image/Q2.bmp"); ledTwinkle(); break;
                case 3: bmp_read("./Q1image/Q3.bmp"); ledTwinkle(); break;
                case 2: bmp_read("./Q1image/Q4.bmp"); ledTwinkle(); break;
                case 1: bmp_read("./Q1image/Q5.bmp"); ledTwinkle(); break;
                case 0: bmp_read("./gameimage/game1_start.bmp"); ledTwinkle(); break;
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
                case 4: bmp_read("./Q1image/Q7.bmp"); ledTwinkle(); break;
                case 3: bmp_read("./Q1image/Q8.bmp"); ledTwinkle(); break;
                case 2: bmp_read("./Q1image/Q9.bmp"); ledTwinkle(); break;
                case 1: bmp_read("./Q1image/Q10.bmp"); ledTwinkle(); break;
                case 0: bmp_read("./gameimage/game2_start.bmp"); ledTwinkle(); break;
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

static void* ledTwinkleTHFunc(void*arg){
    ledTwinkle();
}

static void* colorledTHFunc(void*arg){
    pwmLedInit();
    pwmLedRainbow(colortime);
    pwmLedDorm(10);
    pwmInactiveAll();
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
    

    lcdtextwrite(str1,"",1);
    lcdtextwrite("",str2,2);
    fndOff();
    pwmActiveAll();
    pwmLedDorm(0);

    //터치하면 질문단계로 넘기기
    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);

    pthread_create(&start_on_offTH_ID, NULL, start_on_onTHFunc, NULL);
    pthread_join(start_on_offTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);
    
    //해리포터 노래 시작
    pthread_create(&music1TH_ID, NULL, music1THFunc, NULL);
    pthread_detach(music1TH_ID);

    //텍스트LCD 시작 모든 과정이 끝나면 쓰레드 종료시킴 in result func
 
    //인트로 jpgAnimation dispaly
    pthread_create(&start_read_jpgTH_ID, NULL, read_jpg_start, NULL);
    pthread_join(start_read_jpgTH_ID, NULL);
    sleep(1);
}

void Question_1(void){

    leave_Q = 5; 

    //질문 버튼 누르면 하나씩 화면 바뀌고 index값 반영
    pthread_create(&touchTH_ID2, NULL, touchTHFunc2, NULL);
    pthread_detach(touchTH_ID2);

    pthread_create(&bmpTH_ID_1, NULL, bmpTHFunc1, NULL);
    pthread_detach(bmpTH_ID_1);

    while(leave_Q != 0){ usleep(100000);}
       touchExit();
    sleep(1);
    pthread_cancel(touchTH_ID2);
    pthread_cancel(bmpTH_ID_1);

    //해리포터 노래 끝
    buzzerStopSong();
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
    
    //5초동안 부저 led울리기 (측정중)
    pthread_create(&colorledTH_ID, NULL, colorledTHFunc, NULL);
    pthread_detach(colorledTH_ID);
    pthread_create(&buzzercountdownTH_ID, NULL, buzzercountdownTHFunc, NULL);
    pthread_detach(buzzercountdownTH_ID);
    pthread_create(&ledCountdownTH_ID, NULL, ledcountdownTHFunc, NULL);
    pthread_detach(ledCountdownTH_ID);
    sleep(5);

    //값 받아 드리기
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

    //게임 끝 효과음
    pthread_create(&music2TH_ID, NULL, music2THFunc, NULL);
    pthread_detach(music2TH_ID);
    start_on_off = 1;
    usleep(100);

    //터치 입력받으면 두번째 질문으로 넘어가기
    pthread_create(&touchTH_ID1, NULL, touchTHFunc1, NULL);
    pthread_detach(touchTH_ID1);
    pthread_create(&game1_endTH_ID, NULL, game1_endTHFunc, NULL);
    pthread_join(game1_endTH_ID, NULL);
        touchExit();
    pthread_cancel(touchTH_ID1);
}

void Question_2(void){
    leave_Q = 5; 
    //해리포터 노래 다시 시작
    pthread_create(&music1TH_ID, NULL, music1THFunc, NULL);
    pthread_detach(music1TH_ID);
    
    //질문 버튼 누르면 하나씩 화면 바뀌고 index값 반영
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
    int numIterations = 100;    //iteration     (     Ƚ  )
    int totalTime = 10;         //      ð      
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

    //해리포터 노래 종료
        buzzerStopSong();
    pthread_cancel(music1TH_ID);
    

    //센즈 읍악 시작
    pthread_create(&music3TH_ID, NULL, music3THFunc, NULL);
    pthread_detach(music3TH_ID);

    //빗자루 설명 10초간 띄우기
    fndCountdown(10);
    bmp_read("./groomimage/broom_0.bmp");

    counterdownnum = 24;

    //빗자루 게임 시작
    pthread_create(&fndCountdownTH_ID, NULL, fndcountdownTHFunc, NULL);
    pthread_detach(fndCountdownTH_ID);


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
            area = 0;  bmp_read("./groomimage/broom_0.bmp");        
        }
        else{
            if (0 <= angle && angle < 15) {
                area = 1;
                ++broomscore;bmp_read("./groomimage/broom_19.bmp");
            }
            else if (15 <= angle && angle < 30) {
                area = 2;
                ++broomscore; bmp_read("./groomimage/broom_18.bmp");
            }
            else if (30 <= angle && angle < 45) {
                area = 3;
                ++broomscore; bmp_read("./groomimage/broom_17.bmp");
            }
            else if (45 <= angle && angle < 60) {
                area = 4;
                ++broomscore; bmp_read("./groomimage/broom_16.bmp");
            }
            else if (60 <= angle && angle < 75) {
                area = 5;
                ++broomscore; bmp_read("./groomimage/broom_15.bmp");
            }
            else if (75 <= angle && angle < 90) {
                area = 6;
                ++broomscore;bmp_read("./groomimage/broom_14.bmp");
            }
            else if (90 <= angle && angle < 105) {

                area = 7;
                ++broomscore;bmp_read("./groomimage/broom_13.bmp");
            }
            else if (105 <= angle && angle < 120) {

                area = 8;
                ++broomscore;bmp_read("./groomimage/broom_12.bmp");
            }
            else if (120 <= angle && angle < 135) {

                area = 9;
                ++broomscore;bmp_read("./groomimage/broom_11.bmp");
            }
            else if (135 <= angle && angle < 150) {

                area = 10;
                ++broomscore;bmp_read("./groomimage/broom_10.bmp");
            }
            else if (150 <= angle && angle < 165) {

                area = 11;
                ++broomscore;bmp_read("./groomimage/broom_9.bmp");
            }
            else if (165 <= angle && angle < 180) {

                area = 12;
                ++broomscore;bmp_read("./groomimage/broom_8.bmp");
            }
            else if (180 <= angle && angle < 195) {
                area = 13;
                ++broomscore;bmp_read("./groomimage/broom_7.bmp");
            }
            else if (195 <= angle && angle < 210) {
                area = 14;
                ++broomscore;bmp_read("./groomimage/broom_6.bmp");
            }
            else if (210 <= angle && angle < 225) {
                area = 15;
                ++broomscore;bmp_read("./groomimage/broom_5.bmp");
            }
            else if (225 <= angle && angle < 240) {
                area = 16;
                ++broomscore;bmp_read("./groomimage/broom_4.bmp");
            }
            else if (240 <= angle && angle < 255) {
                area = 17;
                ++broomscore;bmp_read("./groomimage/broom_3.bmp");
            }
            else if (255 <= angle && angle < 270) {
                area = 18;
                ++broomscore;bmp_read("./groomimage/broom_2.bmp");
            }
            else if (270 <= angle && angle < 285) {
                area = 19;
                ++broomscore;bmp_read("./groomimage/broom_1.bmp");
            }
            else if (285 <= angle && angle < 300) {
                area = 20;
                ++broomscore;bmp_read("./groomimage/broom_24.bmp");
            }
            else if (300 <= angle && angle < 315) {
                area = 21;
                ++broomscore;bmp_read("./groomimage/broom_23.bmp");
            }
            else if (315 <= angle && angle < 330) {
                area = 22;
                ++broomscore;bmp_read("./groomimage/broom_22.bmp");
            }
            else if (330 <= angle && angle < 345) {
                area = 23;
                ++broomscore;bmp_read("./groomimage/broom_21.bmp");
            }
            else if (345 <= angle && angle <= 360) {
                area = 24;
                ++broomscore;bmp_read("./groomimage/broom_20.bmp");
            }
        }
        printf("Area : %d\n", area);
        usleep(delay);
    }

    // Game ended. Printing result
    printf("\n\nScore : %d\n", broomscore);

    // 빗자루 게임 종료후 index 값 반영
    if(0 <= broomscore && broomscore < 25){S = S + 6;}
    else if(25 <= broomscore && broomscore < 50){G = G + 6;}
    else if(50 <= broomscore && broomscore < 75){H = H + 6;}
    else if(75 <= broomscore && broomscore <=100){R = R + 6;}
    else printf("Score calculating error!");
    
    //빗자루 게임 끝 이미지 띄우고 샌즈 음악 끄기
    bmp_read("./gameimage/game2_done.bmp");
        buzzerStopSong();
    pthread_cancel(music3TH_ID);

    start_on_off = 1;
    usleep(1000);

    //게임 끝 효과음 
    pthread_create(&music2TH_ID, NULL, music2THFunc, NULL);
    pthread_detach(music2TH_ID);

    // 화면 터치되면 인데스 값에 따라 기숙사 배정하기
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

    //배정된 기숙사에 따라 부가적인 정보를 담은 QR코드 띄우기
    if(tmp==S)      snprintf(QRfilename,50,"./QRimage/QRS.bmp");
    else if(tmp==G) snprintf(QRfilename,50, "./QRimage/QRG.bmp");
    else if(tmp==R) snprintf(QRfilename,50, "./QRimage/QRR.bmp");
    else if(tmp==H) snprintf(QRfilename,50, "./QRimage/QRH.bmp");
    bmp_read(QRfilename);   
}


int main(void){
    start();

    Question_1();
    
    game1();

    Question_2();

    game2();

    result();

    return 0;
}