all: libMyPeri.a

libMyperi.a: led.o button.o buzzer.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o button.o buzzer.o 

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

button.o: button.c button.h
	arm-linux-gnueabi-gcc -c button.c -o button.o

buzzer.o: buzzer.c buzzer.h
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
