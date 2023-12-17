#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "led.h"
#include "buzzer.h"

static pthread_t LedCountTH;
static pthread_t BuzzerCountTH;

void *LedCountThFunc(void* arg) {
    ledCountdown(8);
    pthread_exit(NULL);
}

void *BuzzerCountThFunc(void* arg) {
    buzzerCountdown(8);
    pthread_exit(NULL);
}

int main(void) {
    pthread_create(&LedCountTH, NULL, LedCountThFunc, NULL);
    pthread_create(&BuzzerCountTH, NULL, BuzzerCountThFunc, NULL);

    pthread_detach(LedCountTH);
    pthread_detach(BuzzerCountTH);
    
	sleep(10);
    return 0;
}