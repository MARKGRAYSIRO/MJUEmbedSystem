#include <unistd.h>
#include "screen.h"

int main(void){
    bmp_read("./game1/game1_manu.bmp");

    sleep(2);
    bmp_read("./game1/game1_done.bmp");
    return 0;
}