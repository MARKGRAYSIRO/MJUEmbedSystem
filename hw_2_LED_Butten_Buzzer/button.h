#ifndef _BUTTON_H_
#define _BUTTON_H_

#define MESSAGE_ID 1122
typedef struct
{
    long int messgeNum;
    int ketInput;
    int pressed;
}   BUTTON_MSG_T;

int buttonInit(void);
int nuttonExit(void);
#endif