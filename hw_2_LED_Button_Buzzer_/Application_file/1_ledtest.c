#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define LED_DRIVER_NAME "/dev/periled"

int main(int argc, char **argv){
    unsigned int data = 0;
    int fd;
    if(argc < 2){
        perror("Args number is less than two\n");
        return 1;
    }
    data = strtol(argv[1],NULL,16);
    printf("wrate data :0x%X\n",data);

    fd=open(LED_DRIVER_NAME, O_RDWR);
    if(fd < 0){
        perror("driver (//dev//cnled) open error.\n");
        return 1;
    }
    write(fd, &data, 4);

    close(fd);
    return 0;
}