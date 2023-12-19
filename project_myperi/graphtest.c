#include <stdio.h>
#include <unistd.h>
#include "screen.h"


int main(void){

bmp_read("./gameimage/game1_start.bmp");
sleep(2);
bmp_read("./gameimage/game1_ing.bmp");
sleep(2);
bmp_read("./gameimage/game2_start.bmp");
sleep(2);
bmp_read("./game1/game1_done.bmp");
sleep(2);
bmp_read("./game1/game1_manu.bmp");
sleep(2);
return 0;

}










