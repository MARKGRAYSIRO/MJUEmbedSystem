
final.elf : 1.o 2.o 3.o 4.o myProject.h
	gcc  -o final.elf 1.o 2.o 3.o 4.o main.c
1.o : 1.c
	gcc -c 1.c
2.o : 2.c
	gcc -c 2.c
3.o : 3.c
	gcc -c 3.c
4.o : 4.c
	gcc -c 4.c


