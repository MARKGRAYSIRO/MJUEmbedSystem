#ifndef _BUZZER_H_
#define _BUZZER_H_

int buzzerInit(void);
int buzzerPlaySong(int scale);
int buzzerStopSong(void);
int buzzerExit(void);
int buzzerPlaySong2(int scale);
int buzzerPlaySong3(int scale);
void buzzerEnable(int en);

#endif
