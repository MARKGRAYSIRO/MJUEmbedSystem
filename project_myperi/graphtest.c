#include <stdio.h>
#include <unistd.h>
#include "screen.h"


int main(void){

bmp_read("./start_on_off/start_on.bmp");
int i;

for(i = 0; i < 10; i++){


    bmp_read2("./ball.bmp",i*10,i*10);
    usleep(500000);


}

}










