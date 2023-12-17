#ifndef TEMP_H
#define TEMP_H

#include <stdint.h>

// Function prototypes
int spi_init(char filename[40]);
char *spi_read_lm74(int file);

#endif // TEMP_H
