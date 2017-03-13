CC=gcc
CFLAGS=-lm -O2
CFLAGS=-O2
all:;!ERROR You must specify win|linux

linux:library
win:library.exe

library.exe:./src/slib.h ./src/library.c slib.dll
	$(CC) src/library.c slib.dll  -o library $(CFLAGS) -DPLAT=1

library:./src/slib.h ./src/library.c slib.so
	$(CC) src/library.c slib.so  -o library $(CFLAGS) -DPLAT=0
.PHONY:clean
	$(REMOVE) *.o
