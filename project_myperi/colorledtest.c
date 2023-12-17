#include <stdio.h>
#include <unistd.h> // usleep 함수를 위한 헤더
#include "colorled.h"

void setColor(int r, int g, int b);

int main() {
    char color;
    pwmLedInit();

    // 주기(period)를 짧게 설정하여 부드러운 색상 전환 효과를 얻음
    pwmSetPeriod(20000, 0); // 20ms 주기로 설정
    pwmSetPeriod(20000, 1);
    pwmSetPeriod(20000, 2);

    for(int i = 0; i < 16; i++) {
        switch(i % 4) {
            case 0: setColor(100, 0, 0); break; // 빨간색
            case 1: setColor(0, 100, 0); break; // 초록색
            case 2: setColor(0, 0, 100); break; // 파란색
            case 3: setColor(100, 100, 0); break; // 노란색
        }
        usleep(500000); // 0.5초 대기
    }

      // 사용자 입력에 따른 색상 표시
    printf("Enter the color (r, g, b, y): ");
    scanf(" %c", &color);

    switch(color) {
        case 'r': setColor(100, 0, 0); break;
        case 'g': setColor(0, 100, 0); break;
        case 'b': setColor(0, 0, 100); break;
        case 'y': setColor(100, 100, 0); break;
        default:
            printf("Invalid color!\n");
            pwmInactiveAll();
            return -1;
    }

    printf("Press Enter to exit...\n");
    getchar(); // 사용자가 엔터를 누를 때까지 대기
    getchar(); // 두 번 호출: 첫 번째는 scanf에서 남은 엔터, 두 번째는 사용자 입력



    pwmInactiveAll();
    return 0;
}

void setColor(int r, int g, int b) {
    pwmStartAll();
    pwmSetPercent(r, 0); // 빨간색 밝기 설정
    pwmSetPercent(g, 1); // 초록색 밝기 설정
    pwmSetPercent(b, 2); // 파란색 밝기 설정
    if(r == 0) {disable(0);}
    if(g == 0) {disable(1);}
    if(b == 0) {disable(2);}
}