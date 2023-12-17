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
#include "temperature.h"


char gbuf[10];

int spi_init(char filename[40])
{
	int file;
	__u8  mode, lsb, bits;
	__u32 speed=20000;

	if ((file = open(filename,O_RDWR)) < 0)
	{
		printf("Failed to open the bus.");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		printf ("ErrorTYpe:%d\r\n",errno);
		exit(1);
	}

	//possible modes: mode |= SPI_LOOP; mode |= SPI_CPHA; mode |= SPI_CPOL; mode |= SPI_LSB_FIRST; mode |= SPI_CS_HIGH; mode |= SPI_3WIRE; mode |= SPI_NO_CS; mode |= SPI_READY;
	mode |= SPI_3WIRE ; 

	if (ioctl(file, SPI_IOC_RD_MODE, &mode) < 0)
	{
		perror("SPI rd_mode");
		return 0;
	}
	if (ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)
	{
		perror("SPI rd_lsb_fist");
		return 0;
	}
	if (ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) 
	{
		perror("SPI bits_per_word");
		return 0;
	}
 
printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n",filename, mode, bits, lsb ? "(lsb first) " : "", speed); 
    return file;
}

 char * spi_read_lm74(int file)
{
	int len;

	memset(gbuf, 0, sizeof( gbuf));
	len = read(file, gbuf, 2);
	if (len !=2)
	{
		perror("read error");
		return NULL;
	}

	return gbuf;
}

/*int printTemp(void)
{
	char *buffer;
	int file;
	 
	file=spi_init("/dev/spidev1.0"); //dev

	buffer=(char *)spi_read_lm74(file); 
	 
	close(file);

	int value = (buffer[0] << 8 ) | buffer[1];
	if ( value < 0 )
	{
		value = (int)(value^(-1));
	}
	value >>= 7; // unit 1 
	printf("temperature: %d \n", value);

	return 0;
}*/

int printTemp(void) {
    char *buffer;
    int file;

    file = spi_init("/dev/spidev1.0");
    buffer = (char *)spi_read_lm74(file);
    close(file);

    if (buffer == NULL) {
        printf("Error reading temperature\n");
        return -1;
    }

    int raw_value = ((buffer[0] << 8) | buffer[1]) >> 3; // 상위 13비트 추출
    float temperature;

    if (raw_value & 0x1000) { // 13비트가 1이면 음수
        // 상위 비트를 버린 후, 음수로 변환
        temperature = -((float)((raw_value ^ 0x1FFF) + 1) / 16.0);
    } else {
        // 양수로 변환
        temperature = (float)raw_value / 16.0;
    }

    printf("Temperature: %.3f°C\n", temperature);

    return 0;
}
