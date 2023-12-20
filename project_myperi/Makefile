all: project.elf

project.elf: project.c libMyperi.a libjpeg.a libmylib.a
	arm-linux-gnueabi-gcc project.c -o project.elf -lMyperi -L. -pthread -ljpeg -L. -lmylib

libMyperi.a: jpeglib.h libfbdev.h led.o button.o buzzer.o fnd.o lcdtext.o colorled.o accelMagGyro.o touch.o temperature.o screen.o jpgAnimation.o
	arm-linux-gnueabi-ar rc libMyperi.a led.o button.o buzzer.o fnd.o lcdtext.o colorled.o accelMagGyro.o touch.o temperature.o screen.o jpgAnimation.o

jpgAnimation.o: jpgAnimation.c jpgAnimation.h jpeglib.h libfbdev.h
	arm-linux-gnueabi-gcc -c -o jpgAnimation.o jpgAnimation.c 

led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o

button.o: button.c button.h
	arm-linux-gnueabi-gcc -c button.c -o button.o

buzzer.o: buzzer.c buzzer.h
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o

fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

lcdtext.o: lcdtext.h lcdtext.c
	arm-linux-gnueabi-gcc -c lcdtext.c -o lcdtext.o

colorled.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o

accelMagGyro.o: accelMagGyro.h accelMagGyro.c
	arm-linux-gnueabi-gcc -c accelMagGyro.c -o accelMagGyro.o

touch.o: touch.h touch.c
	arm-linux-gnueabi-gcc -c touch.c -o touch.o

temperature.o: temperature.h temperature.c
	arm-linux-gnueabi-gcc -c temperature.c -o temperature.o

screen.o: screen.c screen.h
	arm-linux-gnueabi-gcc -c screen.c -o screen.o

clean:
	rm -f *.o 
	rm -f libMyperi.a
