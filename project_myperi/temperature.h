#ifndef __TEMPERATURE_H__

int printTemp(void);
float getTemp(void);

int spi_init(char filename[40]);

 char * spi_read_lm74(int file);
 
 #endif
