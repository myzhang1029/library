CC=gcc
CFLAGS=-lm -O2 -L. -lsbl
RM=rm

err:
	@echo "You must specify win|unix"

unix:library
win:library.exe

library.exe:./src/slib.h ./src/library.c
	$(CC) $(CFLAGS) -DPLAT=1 src/library.c -o library

library:./src/slib.h ./src/library.c
	$(CC) $(CFLAGS) -DPLAT=0 src/library.c -o library

.PHONY:clean

clean:
	$(RM) *.o
