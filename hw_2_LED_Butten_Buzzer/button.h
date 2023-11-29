#ifndef _BUTTON_H_
#define _BUTTON_H_

#define MESSAGE_ID 1122
typedef struct
{
    long int messgeNum; //8byte
    int keyInput = 0;
    int pressed;
}   BUTTON_MSG_T;
/*
struct input_event {
    struct timeval time; //아마도 디바이스 드라이버에 존재함
    __u16 type;
    __u16 code;
    __s32 value;
}*/

int buttonInit(void);
int buttonExit(void);
#endif