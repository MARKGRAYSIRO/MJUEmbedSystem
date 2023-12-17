#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include "touch.h"

int main(void) {
    touchInit();

    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    BUTTON_MSG_T recvMsg;

    while (1) {
        msgrcv(msgID, &recvMsg, sizeof(recvMsg) - sizeof(long int), 0, 0);
        printf("%d, %d",recvMsg.x, recvMsg.y);
        if (recvMsg.keyInput == 999 && recvMsg.pressed == 1) {
            if (recvMsg.x <= 120) {
                printf("%d, %d",recvMsg.x, recvMsg.y);
                printf("Question area touched!\r\n");
            }
            else if (recvMsg.x > 240 && recvMsg.x <= 360) {
                printf("%d, %d",recvMsg.x, recvMsg.y);
                printf("Answer 1 touched!\r\n");
            }
            else if (recvMsg.x > 480 && recvMsg.x <= 600) {
                printf("%d, %d",recvMsg.x, recvMsg.y);
                printf("Answer 2 touched!\r\n");
            }
            else if (recvMsg.x > 600 && recvMsg.x <= 800) {
                printf("%d, %d",recvMsg.x, recvMsg.y);
                printf("Answer 3 touched!\r\n");
            }
            /*else if (recvMsg.y > 130 && recvMsg.y <= 140) {
                printf("Answer 4 touched!\r\n");
            }*/
            else {
                printf("Out of bounds touch: X=%d, Y=%d\r\n", recvMsg.x, recvMsg.y);
            }
        }
        }
    }
