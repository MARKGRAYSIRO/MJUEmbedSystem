
final.elf : 1.o 2.o
	gcc  -o final.elf 1.o 2.o 3.c 4.c main.c myProject.h 	
1.o : 1.c
	gcc -c 1.c
2.o : 2.c
	gcc -c 2.c

