#ifndef _LED_H_
#define _LED_H_
#define LED_DRIVER_NAME "/dev/periled"

int ledLibInit(void);
int ledOnOff (int ledNum, int onoff);
int ledstatus (void);
int ledLibExit(void);
void ledCountdown(int count);
void ledTwinkle(void);

#endif