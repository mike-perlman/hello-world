 rm mps7 
 rm *.o
 gcc -c -g3 -O0 -fmessage-length=0 -std=c99 -Wall -o bitsbytes.o bitsbytes.c
 gcc -c -g3 -O0 -fmessage-length=0 -std=c99 -Wall -o mps7.o mps7.c
 gcc -c -g3 -O0 -fmessage-length=0 -std=c99 -Wall -o main.o main.c
 gcc -g3 -std=c99 -O0 -fmessage-length=0 -Wall -lm -o mps7 main.o mps7.o bitsbytes.o 
