#include <stdio.h>
#include <stdlib.h>     // for exit
#include <unistd.h>     // for open/close
#include <fcntl.h>      // for O_RDWR
#include <sys/ioctl.h>  // for ioctl
#include <sys/mman.h>
#include <linux/fb.h>   // for fb_var_screeninfo, FBIOGET_VSCREENINFO
#include "bitmap.h"

#define FBDEV_FILE  "/dev/fb0" // nodefile for using memory
#define BIT_VALUE_24BIT   24

int main (void)
{
   for(int i=1;i<5;i++){
	   char filename[200]={0,};
	   snprintf(filename,200,"./%d.bmp",i);
	   bmp_read (filename);

	   }
    return 0;
}
