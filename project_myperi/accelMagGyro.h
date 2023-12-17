#ifndef __accelMagGyro_H__

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

int printAccel(void);
int printMag(void);
int printGyro(void);
int getAccel(int* accel);
int getMag(int* magne);
int getGyro(int *gyro);
 
 #endif
