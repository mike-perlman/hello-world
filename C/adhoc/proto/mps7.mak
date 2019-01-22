SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .c .o
CFLAGS = -c -g3 -O0 -fmessage-length=0 -std=c99 -Wall
LFLAGS = -g3 -std=c99 -O0 -fmessage-length=0 -Wall -lm
srcdir = src
CC = gcc

mps7: bitsbytes.o mps7.o main.o
	$(CC) $(LFLAGS) -o $@ bitsbytes.o mps7.o main.o

main.o : $(srcdir)\main.c
	$(CC) $(CFLAGS) -o $@ $<

bitsbytes.o : $(srcdir)\bitsbytes.c
	$(CC) $(CFLAGS) -o $@ $<

mps7.o : $(srcdir)\mps7.c
	$(CC) $(CFLAGS) -o $@ $<

  
clean: 
	rm *.o mps7.exe
