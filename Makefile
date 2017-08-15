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
	cd slib;./configure --cc=$(CC) --target=win --prefix='../'
	make -C slib&&make -C slib install
	$(CC) library.c -o library $(CFLAGS) -DPLAT=1 libsbl.a

library:library.c
	@if ! [ -f slib/Makefile ] ; then\
		echo slib/Makefile not found!;\
		echo Is this project cloned with --recursive option?;\
		echo If not, please do 'git submodule init&&git submodule update';\
	exit 1;\
	fi
	cd slib;./configure --cc=$(CC) --target=unix --prefix='../'
	make -C slib&&make -C slib install
	$(CC) library.c -o library $(CFLAGS) -DPLAT=0 libsbl.a
.PHONY:clean
clean:
	$(RM) *.o
	make -C slib distclean
