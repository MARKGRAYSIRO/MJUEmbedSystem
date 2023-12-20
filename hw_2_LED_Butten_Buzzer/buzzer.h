#ifndef _BUZZER_H_
#define _BUZZER_H_

int buzzerInit(void);
int buzzerPlaySong(int scale);
int buzzerPlaySong2(int scale);
int buzzerPlaySong3(int scale);
int buzzerStopSong(void);
int buzzerExit(void);
void buzzerCountdown(int count);
void beat1(float beat);
void beat2(float beat);
void beat3(float beat);
void rest2(float beat);
void rest3(float beat);

#endif
