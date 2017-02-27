CC=tcc
REMOVE=del
EXTEND=dll

./build/slib.$(EXTEND):./src/slib.h ./src/library.c ./build/slib.$(EXTEND)
	$(CC) ./src/library.c ./build/slib.&(EXTEND)  -o ./build/library
rmsrc:
	$(REMOVE) buildlibrary.bat buildlibrary.sh .gitignore .gitattributes /src/* 
