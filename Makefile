CC=gcc
RM=rm
CFLAGS=-lm -O2 -Wall -L. -lsbl -Islib/include
err:
	@echo 'Please do make PLATFORM:'
	@echo '	win:Windows, MinGW'
	@echo '	unix:UNIX, GNU/Linux, BSD'
	@exit 1

unix:library
win:library.exe

library.exe:library.c 
	@if ! [ -f slib/Makefile ] ; then\
		echo slib/Makefile not found!;\
		echo Is this project cloned with --recursive option?;\
		echo If not, please do 'git submodule init&&git submodule update';\
	exit 1;\
	fi
	cd slib;make win 
	cp slib/libsbl.dll .
	$(CC) library.c -o library $(CFLAGS) -DPLAT=1

library:library.c
	@if ! [ -f slib/Makefile ] ; then\
		echo slib/Makefile not found!;\
		echo Is this project cloned with --recursive option?;\
		echo If not, please do 'git submodule init&&git submodule update';\
	exit 1;\
	fi
	cd slib;make unix
	cp slib/libsbl.so .
	$(CC) library.c -o library $(CFLAGS) -DPLAT=0
.PHONY:clean
	$(RM) *.o
