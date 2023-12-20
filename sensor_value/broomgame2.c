#include <stdio.h>
#include <unistd.h>
#include "accelMagGyro.h"

#define PI 3.14159265358979323846

double custom_atan(double x) {
    if (x > 1.0) {
        return PI / 2 - custom_atan(1 / x);
    }
    else if (x < -1.0) {
        return -PI / 2 - custom_atan(1 / x);
    }

    double result = 0;
    double term = x;
    for (int i = 1; i <= 100; ++i) {
        if (i % 2 != 0) {
            result += (i % 4 == 1) ? term : -term;
        }
        term *= x * x;
    }
    return result;
}

double custom_atan2(double y, double x) {
    if (x > 0) return custom_atan(y / x);
    if (y >= 0 && x < 0) return custom_atan(y / x) + PI;
    if (y < 0 && x < 0) return custom_atan(y / x) - PI;
    if (y > 0 && x == 0) return PI / 2;
    if (y < 0 && x == 0) return -PI / 2;
    return 0; // In case x and y are both zero
}

double to_degrees(double radians) {
    double degrees = radians * (180.0 / PI);
    if (degrees < 0) {
        degrees += 360.0;
    }
    return degrees;
}

void readGyro(int* gyro) {
    if (getAccel(gyro) != 0) {
        printf("Failed to get gyroscope values.\n");
    }
}

int main() {

    int numIterations = 100;    //iteration ����(���� Ƚ��)
    int totalTime = 10;         //���� �ð� ����
    int delay = totalTime * 1000000 / numIterations;

    int gyro[3];
    int area = 0;
    int broomscore = 0;
    int x = 0;
    int y = 0;
    

    // Loop through each set of coordinates
    for (int i = 1; i < numIterations; ++i) {

        readGyro(gyro);

        // Extract x and y values from gyroscope data
        x = gyro[0];
        y = gyro[1];

        double result = custom_atan2(y, x);
        double angle = to_degrees(result);
        
        // Define the position on the Cartesian system
        // Divide area by degrees (15 degrees per area)

        printf("Angle: %f\n", angle);

        if (x > -1000 && x < 1000 && y > -1000 && y < 1000) {
            area = 0;
            bmp_read("./gameimage/game2_start.bmp");
        }
        else if (0 <= angle && angle < 15) {
            area = 1;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (15 <= angle && angle < 30) {
            area = 2;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (30 <= angle && angle < 45) {
            area = 3;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (45 <= angle && angle < 60) {
            area = 4;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (60 <= angle && angle < 75) {
            area = 5;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (75 <= angle && angle < 90) {
            area = 6;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (90 <= angle && angle < 105) {
            area = 7;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (105 <= angle && angle < 120) {
            area = 8;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (120 <= angle && angle < 135) {
            area = 9;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (135 <= angle && angle < 150) {
            area = 10;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (150 <= angle && angle < 165) {
            area = 11;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (165 <= angle && angle < 180) {
            area = 12;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (180 <= angle && angle < 195) {
            area = 13;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (195 <= angle && angle < 210) {
            area = 14;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (210 <= angle && angle < 225) {
            area = 15;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (225 <= angle && angle < 240) {
            area = 16;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (240 <= angle && angle < 255) {
            area = 17;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (255 <= angle && angle < 270) {
            area = 18;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (270 <= angle && angle < 285) {
            area = 19;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (285 <= angle && angle < 300) {
            area = 20;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (300 <= angle && angle < 315) {
            area = 21;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (315 <= angle && angle < 330) {
            area = 22;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (330 <= angle && angle < 345) {
            area = 23;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        else if (345 <= angle && angle <= 360) {
            area = 24;
            bmp_read("./gameimage/game2_start.bmp");
            ++broomscore;
        }
        printf("Area : %d\n", area);
        usleep(delay);
    }

<<<<<<< Updated upstream
    //Game ended. Printing result
    //printf("\n\nScore : %d\n", broomscore);
    bmp_read("./gameimage/game2_start.bmp");

    return 0;
=======
    // Game ended. Printing result
    printf("\n\nScore : %d\n", broomscore);
    // index updates
    if(0 <= broomscore && broomscore < 25){S = S + 6;}
    else if(25 <= broomscore && broomscore < 50){G = G + 6;}
    else if(50 <= broomscore && broomscore < 75){H = H + 6;}
    else if(75 <= broomscore && broomscore < 100){R = R + 6;}
    else printf("Score calculating error!");
>>>>>>> Stashed changes

    return 0;
}