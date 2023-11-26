all: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o
