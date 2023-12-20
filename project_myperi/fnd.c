#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "fnd.h"

typedef struct FNDWriteDataForm_tag{
    char DataNumeric[FND_DATA_BUFF_LEN];
    char DataDot[FND_DATA_BUFF_LEN];
    char DataValid[FND_DATA_BUFF_LEN];
}stFndWriteForm, *pStFndWriteForm;


int fndDisp(int num, int dotflag) {
    int fd;
    int temp, i;
    stFndWriteForm stWriteData;

    memset(&stWriteData, 0, sizeof(stFndWriteForm)); // 구조체 초기화

    if (num < 10) {
        // 한 자리 숫자인 경우
        stWriteData.DataNumeric[MAX_FND_NUM - 1] = num; // 오른쪽 첫 번째 세그먼트에 숫자를 표시
        stWriteData.DataValid[MAX_FND_NUM - 1] = 1;    // 오른쪽 첫 번째 세그먼트만 활성화
    } else {
        // 두 자리 이상의 숫자인 경우
        for (i = MAX_FND_NUM - 1; i >= 0; i--) {
            temp = num % 10;
            stWriteData.DataNumeric[i] = temp;
            stWriteData.DataValid[i] = (num > 0) ? 1 : 0;
            num /= 10;
        }
    }

    for (i = 0; i < MAX_FND_NUM; i++) {
        stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
    }

    fd = open(FND_DRIVER_NAME, O_RDWR);
    if (fd < 0) {
        perror("driver open error.\n");
        return 0;
    }

    write(fd, &stWriteData, sizeof(stFndWriteForm));
    close(fd);
    return 1;
}

int fndOff()
{
	int fd,i;
	stFndWriteForm stWriteData;
	
	for (i = 0; i < MAX_FND_NUM ; i++ )
	{
		stWriteData.DataDot[i] =  0;  
		stWriteData.DataNumeric[i] = 0;
		stWriteData.DataValid[i] = 0;
	}
	fd = open(FND_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver open error.\n");
		return 0;
	}	
	write(fd,&stWriteData,sizeof(stFndWriteForm));
	close(fd);
	return 1;
}

/*void fndCountdown(int count){
    int i;
    for(i =count; i >=0 ; i--){
    fndDisp(i, 0b0000001);
    sleep(1);
    }
    fndOff();
}
*/

void fndCountdown(int count) {
    int remaining_sec, remaining_ms;

    while (count > 0) {
        remaining_sec = count; // 초 단위 남은 시간
        remaining_ms = 0; // 밀리초 단위 남은 시간 (여기서는 사용하지 않음)

        // FND에 남은 시간 표시 (예: 5)
        fndDisp(remaining_sec, 0b010000); // 밀리초 단위 표시를 위한 두 번째 인자는 선택 사항

        // 1초 대기
        usleep(1000000);

        // 카운트다운 감소
        count--;
    }

    fndOff(); // FND 끄기
}

/*
int fndDisp(int num, int dotflag){
    int fd;
    int temp, i;
    stFndWriteForm stWriteData;
    for(i = 0; i < MAX_FND_NUM; i++){
        stWriteData.DataDot[i] = (dotflag&(0x1 << i)) ? 1:0;
        stWriteData.DataValid[i] = 1;
    }

    temp = num % 1000000;
    stWriteData.DataNumeric[0] = temp / 100000;
    temp = num % 100000;
    stWriteData.DataNumeric[1] = temp / 10000;
    temp = num % 10000;
    stWriteData.DataNumeric[2] = temp / 1000;
    temp = num % 1000;
    stWriteData.DataNumeric[3] = temp / 100;
    temp = num % 100;
    stWriteData.DataNumeric[4] = temp / 10;
    stWriteData.DataNumeric[5] = num % 10;

    fd = open(FND_DRIVER_NAME, O_RDWR);
    if (fd < 0){
        perror("driver open error. \n");
        return 0;
    }
    write(fd, &stWriteData, sizeof(stFndWriteForm));
    close(fd);
    return 1;
}
*/