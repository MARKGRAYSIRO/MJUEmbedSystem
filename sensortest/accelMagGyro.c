#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "accelMagGyro.h"

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
