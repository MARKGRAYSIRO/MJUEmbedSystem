#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "lcdtext.h"

typedef struct TextLCD_tag{
    unsigned char cmd;
    unsigned char cmdData;
    unsigned char reserved[2];
    char TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;

int lcdtextwrite(const char *str1, const *str2, int lineFlag){
    unsigned int linenum = 0;
    stTextLCD stlcd;
    int fd;
    int len;
    int len0;
    memset(&stlcd, 0, sizeof(stTextLCD));

    linenum = lineFlag;
    printf("hello, start!\n");
    printf("linenum: %d\n", linenum);
    if(linenum == 1)
        stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
    else if(linenum == 2)
        stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
    else if(linenum == 3)
        stlcd.cmdData = CMD_DATA_WRITE_BOTH_LINE;
    else{
        printf("linenum: %d wrong . range(1~3)\n", linenum);
        return 1;
    }

    if (stlcd.cmdData == 0){
        len = strlen(str1);
        if(len > COLUMN_NUM)
            memcpy(stlcd.TextData[0], str1, COLUMN_NUM);
        else
            memcpy(stlcd.TextData[0], str1, len);
        len0 = strlen(str2);
        if(len0 > COLUMN_NUM)
            memcpy(stlcd.TextData[stlcd.cmdData-1], str2, COLUMN_NUM);
        else
            memcpy(stlcd.TextData[stlcd.cmdData-1], str2, len);
    }

    else if(stlcd.cmdData == 1){
        len = strlen(str1);
        if(len > COLUMN_NUM)
            memcpy(stlcd.TextData[stlcd.cmdData-1], str1, COLUMN_NUM);
        else
            memcpy(stlcd.TextData[stlcd.cmdData-1], str1, len);
    }

    else{
        len = strlen(str2);
        if(len > COLUMN_NUM)
            memcpy(stlcd.TextData[stlcd.cmdData-1], str2, COLUMN_NUM);
        else   
            memcpy(stlcd.TextData[stlcd.cmdData-1], str2, len);
    }

    stlcd.cmd = CMD_WRITE_STRING;
    fd = open(TEXTLCD_DRIVER_NAME, O_RDWR);
    if (fd < 0){
        perror("driver(//dev//peritextlcd) open error.\n");
        return 1;
    }
    
    write(fd, &stlcd, sizeof(stTextLCD));
    close(fd);
    return 0;
}