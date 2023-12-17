#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "temp.h"

char gbuf[10];

int spi_init(char filename[40])
{
    int file;
    __u8 mode, lsb, bits;
    __u32 speed = 20000;

    if((file = open(filename, O_RDWR)) < 0)
    {
        printf("Failed to open the bus.");
        printf("ErrorType:%d\r\n", errno);
        exit(1);
    }

/*possible modes:
mode |= SPI_LOOP;
mode |= SPI_CPHA;
mode |= SPI_CPOL;
mode |= SPI_LSB_FIRST;
mode |= SPI_CS_HIGH;
mode |= SPI_3WIRE;
mode |= SPI_NO_CS;
mode |= SPI_READY;
*/

    if(ioctl(file, SPI_IOC_RD_MODE, &mode) < 0)
    {
        perror("SPI rd_mode"); //세팅된 SPI 전송 모드를 확인(mode에 저장)
        return 0;
    }
    if(ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)
    {
        perror("SPI rd_lsb_first"); //세팅된 SPI 전송 LSB 순서를 확인(lsb에 저장)
        return 0;
    }
    if(ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
    {
        perror("SPI bits_per_word"); //세팅된 SPI 전송 1word bit 개수를 확인(bits에 저장)
        return 0;
    }

    printf("%s: spi mode %d, %d bits %sper word, %d Hz max.\n", filename, mode, bits, lsb ? "(lsb first)" : "", speed);
    return file;
}

char * spi_read_lm74(int file)
{
    int len;

    memset(gbuf, 0, sizeof(gbuf));
    len = read(file, gbuf, 2);      //Read 2 byte
    if(len != 2)
    {
        perror("read eror");
        return NULL;
    }

    return gbuf;
}

int main(int argc, char **argv)
{
    char *buffer;
    int file;
    file = spi_init("/dev/spidev1.0");  //dev파일
    buffer = (char *)spi_read_lm74(file);
    close(file);

    int value = 0;  //13비트 Big Endian signed int를 Little Endian signed int로 바꾼다
    value = (buffer[1] >> 3);   //Last 3bit: Trashes 날려버리는 함수, 남은 5비트만 value에 더해짐
    value = (value & 0x1F) | ((buffer[0]) << 5);    //위에서 5비트 더한것에 상위 8비트(=13비트)를 원하는 값으로 채움
    //shift연산은 먼저 operand를 'integer'로 바꾸고 나서 일어남. 부호비트에 주의

    double temp = (double)value * 0.0625;   //1비트가 0.0625도
    printf("Current Temp: %lf \n", temp);
    return 0;
}