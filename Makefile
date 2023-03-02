test.exe: test.c functions.h functions.o
	gcc -std=c99 -o test.exe test.c functions.o

functions.o: functions.c functions.h
	gcc -c -std=c99 functions.c