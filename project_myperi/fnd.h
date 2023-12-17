#ifndef __FND_H__
#define __FND_H__

int fndDisp(int num, int dotflg);
int fndOff();

#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
#define FND_DRIVER_NAME "/dev/perifnd"

#endif