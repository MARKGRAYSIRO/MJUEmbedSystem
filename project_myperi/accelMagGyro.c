#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "accelMagGyro.h"

#define PI 3.14159265358979323846

static int fd = 0;
static FILE *fp = NULL;

int printAccel(void){
	fd = open (ACCELPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (ACCELPATH "data", "rt");
	int accel[3];
	fscanf(fp,"%d, %d, %d",&accel[0],&accel[1],&accel[2]);
	printf ("Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
	fclose(fp);
	return 0;
	}

int getAccel(int* accel) {
	fd = open(ACCELPATH "enable", O_WRONLY);
	dprintf(fd, "1");
	close(fd);
	fp = fopen(ACCELPATH "data", "rt");
	fscanf(fp, "%d, %d, %d", &accel[0], &accel[1], &accel[2]);
    return 0;
}

int printMag(void){
	fd = open (MAGNEPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (MAGNEPATH "data", "rt");
	int magne[3];
	fscanf(fp,"%d, %d, %d",&magne[0],&magne[1],&magne[2]);
	printf ("Magneto %d, %d, %d\r\n",magne[0],magne[1],magne[2]);
	fclose(fp);	
	return 0;
	}
int getMag(int* magne){
    fd = open (MAGNEPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (MAGNEPATH "data", "rt");
	fscanf(fp,"%d, %d, %d",&magne[0],&magne[1],&magne[2]);
	return 0;
}

int printGyro(void){
	fd = open (GYROPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (GYROPATH "data", "rt");
	int gyro[3];
	fscanf(fp,"%d, %d, %d",&gyro[0],&gyro[1],&gyro[2]);
	printf ("Gyroscope %d, %d, %d\r\n",gyro[0],gyro[1],gyro[2]);
	fclose(fp);
	return gyro[1];	
	}

int getGyro(int *gyro){
    fd = open (GYROPATH "enable",O_WRONLY);
	dprintf (fd,"1");
	close(fd);
	fp = fopen (GYROPATH "data", "rt");
	fscanf(fp,"%d, %d, %d",&gyro[0],&gyro[1],&gyro[2]);;
	fclose(fp);
    return 0;
}

double custom_atan(double x) {
	    double result = 0;
        double term = x;

    if (x > 1.0) {
        return PI / 2 - custom_atan(1 / x);
    }
    else if (x < -1.0) {
        return -PI / 2 - custom_atan(1 / x);
    }


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
