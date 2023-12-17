#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "fnd.h"

int main(void) {
    int i;
    for (i = 16; i >= 0; i--) {
       
            fndDisp(i, 0b0000001); // 오른쪽에서 두 번째 위치에 점을 표시
       
        getchar(); // 사용자가 엔터 키를 누를 때까지 대기
    }
    return 0;
}