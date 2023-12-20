#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "colorled.h"
#define COLOR_LED_DEV_R_ "/sys/class/pwm/pwmchip0/"
#define COLOR_LED_DEV_G_ "/sys/class/pwm/pwmchip1/"
#define COLOR_LED_DEV_B_ "/sys/class/pwm/pwmchip2/"
#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_DUTY "pwm0/duty_cycle"
#define PWM_PERIOD "pwm0/period"
#define PWM_ENABLE "pwm0/enable"
#define PWM_COLOR_R 0
#define PWM_COLOR_G 1
#define PWM_COLOR_B 2
#define PWM_PERIOD_NS 1000000    //ns. = 1ms = 1khz


void delay(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int pwmActiveAll(void) {
    int fd = 0;
    fd = open(COLOR_LED_DEV_R_ PWM_EXPORT, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"0", 1);
    close(fd);
    fd = open(COLOR_LED_DEV_G_ PWM_EXPORT, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"0", 1);
    close(fd);
    fd = open(COLOR_LED_DEV_B_ PWM_EXPORT, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"0", 1);
    close(fd);
    return 1;
}

int pwmInactiveAll(void) {
    int fd = 0;
    fd = open(COLOR_LED_DEV_R_ PWM_UNEXPORT, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"0", 1);
    close(fd);
    fd = open(COLOR_LED_DEV_G_ PWM_UNEXPORT, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"0", 1);
    close(fd);
    fd = open(COLOR_LED_DEV_B_ PWM_UNEXPORT, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"0", 1);
    close(fd);
    return 1;
}

int pwmSetDuty(int dutyCycle, int pwmIndex) {
    int fd = 0;
    switch (pwmIndex) {
    case 0:
        fd = open(COLOR_LED_DEV_R_ PWM_DUTY, O_WRONLY);
        break;
    case 1:
        fd = open(COLOR_LED_DEV_G_ PWM_DUTY, O_WRONLY);
        break;
    case 2:
        fd = open(COLOR_LED_DEV_B_ PWM_DUTY, O_WRONLY);
        break;
    default:
        fprintf(stderr, "Invalid pwmIndex: %d\n", pwmIndex);
        return -1;
    }
    dprintf(fd, "%d", dutyCycle);
    close(fd);
    return 1;
}

int pwmSetPeriod(int Period, int pwmIndex) {
    int fd = 0;
    switch (pwmIndex) {
    case 0:
        fd = open(COLOR_LED_DEV_R_ PWM_PERIOD, O_WRONLY);
        break;
    case 1:
        fd = open(COLOR_LED_DEV_G_ PWM_PERIOD, O_WRONLY);
        break;
    case 2:
        fd = open(COLOR_LED_DEV_B_ PWM_PERIOD, O_WRONLY);
        break;
    default:
        fprintf(stderr, "Invalid pwmIndex: %d\n", pwmIndex);
        return -1;
    }
    dprintf(fd, "%d", Period);
    close(fd);
    return 1;
}

int pwmSetPercent(int percent, int ledColor) {
    if ((percent) < 0 || (percent > 100)) {
        printf("Wrong percent: %d\r\n", percent);
        return 0;
    }
    int duty = (100 - percent) * PWM_PERIOD_NS / 100;
    //LED Sinking
    pwmSetDuty(duty, ledColor);
    return 0;
}

int pwmStartAll(void) {
    int fd = 0;
    fd = open(COLOR_LED_DEV_R_ PWM_ENABLE, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"1", 1);
    close(fd);
    fd = open(COLOR_LED_DEV_G_ PWM_ENABLE, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"1", 1);
    close(fd);
    fd = open(COLOR_LED_DEV_B_ PWM_ENABLE, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }
    write(fd, &"1", 1);
    close(fd);
    return 1;
}

int disable(int rgb) {
    int fd = 0;
    switch (rgb) {
    case 0: {fd = open(COLOR_LED_DEV_R_ PWM_ENABLE, O_WRONLY);
        if (fd < 0) {
            perror("Failed to open device");
            return -1;
        }
        write(fd, &"0", 1);
        close(fd);
    }
    case 1: {fd = open(COLOR_LED_DEV_G_ PWM_ENABLE, O_WRONLY);
        if (fd < 0) {
            perror("Failed to open device");
            return -1;
        }
        write(fd, &"0", 1);
        close(fd); }
    case 2: {fd = open(COLOR_LED_DEV_B_ PWM_ENABLE, O_WRONLY);
        if (fd < 0) {
            perror("Failed to open device");
            return -1;
        }
        write(fd, &"0", 1);
        close(fd);
    }
    }
    return 1;
}

void pwmLedRainbow(int durationSeconds) {
    int colors[6][3] = {
        //빛의 3원색
        {100, 0, 0},    // Red
        {100, 100, 0},  // Yellow
        {0, 100, 0},    // Green
        {0, 100, 100},  // Cyan
        {0, 0, 100},    // Blue
        {100, 0, 100}   // Magenta
    };

    // Transition between colors
    int steps = 100;
    int i, j;
    for (i = 0; i < 6; i++){
        for (int j = 0; j <= 100; j++) {
        pwmSetPercent(j * colors[i][0] / 100, PWM_COLOR_R);
        pwmSetPercent(j * colors[i][1] / 100, PWM_COLOR_G);
        pwmSetPercent(j * colors[i][2] / 100, PWM_COLOR_B);

        delay(durationSeconds * 1000 / (6 * steps));
        }
    }
}

void pwmLedDorm(int dorm) {
    
    if (dorm == 1) {         // Slytherin (GREEN)
        pwmSetDuty(0, 0);       // set R 0
        pwmSetDuty(100, 1);     // set G 100
        pwmSetDuty(0, 2);       // set B 0       
    }
    else if (dorm == 2) {    // Gryffindor (RED)
        pwmSetDuty(100, 0);     // set R 100
        pwmSetDuty(0, 1);       // set G 0
        pwmSetDuty(0, 2);       // set B 0
    }
    else if (dorm == 3) {    // Ravenclaw (BLUE)
        pwmSetDuty(0, 0);       // set R 0
        pwmSetDuty(0, 1);       // set G 0
        pwmSetDuty(100, 2);     // set B 100       
    }
    else if (dorm == 4) {    // Hufflepuff (YELLOW)
        pwmSetDuty(100, 0);     // set R 100
        pwmSetDuty(100, 1);     // set G 100
        pwmSetDuty(0, 2);       // set B 0        
    }
    else {
        printf("\nInvalid input!\n");
    }

    pwmSetPeriod(PWM_PERIOD_NS, 0);
    pwmSetPeriod(PWM_PERIOD_NS, 1);
    pwmSetPeriod(PWM_PERIOD_NS, 2);
    
}


int pwmLedInit(void) {
    pwmActiveAll();
    pwmSetDuty(0, 0); // set R 0
    pwmSetDuty(0, 1); // set G 0
    pwmSetDuty(0, 2); // set B 0
    pwmSetPeriod(PWM_PERIOD_NS, 0);
    pwmSetPeriod(PWM_PERIOD_NS, 1);
    pwmSetPeriod(PWM_PERIOD_NS, 2);
    pwmStartAll();

    return 0;
}

