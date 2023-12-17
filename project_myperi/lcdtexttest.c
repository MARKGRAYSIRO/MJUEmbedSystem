#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "lcdtext.h"

pthread_t lcdtest_ID;

void* lcdtestFunc(void* argv){
     lcdtextwrite("hi l'am hyunsuk","",1);
     sleep(1);
     lcdtextwrite("","hi i'am myoung g",2);
     sleep(1);
    lcdtextwrite("mjoung ji","",1);
    lcdtextwrite("","university",2);
    sleep(1);
   
}

int main (void){
    pthread_create(&lcdtest_ID, NULL, lcdtestFunc, NULL);
    pthread_join(lcdtest_ID, NULL);
}