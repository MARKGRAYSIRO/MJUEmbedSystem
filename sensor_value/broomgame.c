#include <stdio.h>
#include <unistd.h>
#include "accelMagGyro.h"

<<<<<<< Updated upstream
void readGyro() {
    // Array to store gyroscope data (x, y, z)
    int gyro[3];

    if (getAccel(gyro) != 0) {
        printf("Failed to get gyroscope values.\n");
        return -1;
=======
void readGyro(int* gyro) {
    if (getAccel(gyro) != 0) {
        printf("Failed to get gyroscope values.\n");
>>>>>>> Stashed changes
    }
}

int main() {

    int numIterations = 100;    //iteration 지정(추출 횟수)
    int totalTime = 10;         //측정 시간 지정
    int delay = totalTime * 1000000 / numIterations;

<<<<<<< Updated upstream
=======
    int gyro[3];
>>>>>>> Stashed changes
    int area = 0;
    int broomscore = 0;

    // Loop through each set of coordinates
    for (int i = 1; i < numIterations; ++i) {

<<<<<<< Updated upstream
        readGyro();
=======
        readGyro(gyro);
>>>>>>> Stashed changes

        // Extract x and y values from gyroscope data
        int x = gyro[0];
        int y = gyro[1];

        // Define the position on the Cartesian system
        // Divide area by 3 x 3
        //각 if문 안에 빗자루 사진 코드 삽입할 것
<<<<<<< Updated upstream
        
=======

>>>>>>> Stashed changes
        if (x > -1000 && x < 1000 && y > -1000 && y < 1000) {
            area = 0;
        }
        else if (x > 1000 && y > 1000) {
            area = 1;
            ++broomscore;
        }
<<<<<<< Updated upstream
        else if (x < 1000 && y > -1000 && y < 1000) {
            area = 2;
            ++broomscore;
        }
        else if (x < 1000 && y < -1000) {
=======
        else if (x > 1000 && y > -1000 && y < 1000) {
            area = 2;
            ++broomscore;
        }
        else if (x > 1000 && y < -1000) {
>>>>>>> Stashed changes
            area = 3;
            ++broomscore;
        }
        else if (x > -1000 && x < 1000 && y < -1000) {
            area = 4;
            ++broomscore;
        }
        else if (x < -1000 && y < -1000) {
            area = 5;
            ++broomscore;
        }
        else if (x < -1000 && y > -1000 && y < 1000) {
            area = 6;
            ++broomscore;
        }
        else if (x < -1000 && y > 1000) {
            area = 7;
            ++broomscore;
        }
        else if (x > -1000 && x < 1000 && y > 1000) {
            area = 8;
            ++broomscore;
        }
<<<<<<< Updated upstream
        printf("Area : %d", area);
=======
        printf("Area : %d\n", area);
>>>>>>> Stashed changes
        usleep(delay);
    }

    //Game ended. Printing result
<<<<<<< Updated upstream
    printf("\n\nScore : %d", broomscore);

}

=======
    printf("\n\nScore : %d\n", broomscore);
    return 0;

}
>>>>>>> Stashed changes
