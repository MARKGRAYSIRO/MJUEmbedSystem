#include "colorled.h"
int main(){
    pwmLedInit();
    pwmSetPercent(0, 0);
    pwmSetPercent(50, 1);
    pwmSetPercent(50, 2);
    pwmSetPercent(50, 0);
    pwmSetPercent(0, 1);
    pwmSetPercent(50, 2);
    pwmSetPercent(50, 0);
    pwmSetPercent(50, 1);
    pwmSetPercent(0, 2);
    pwmInactiveAll();
    return 0;

}