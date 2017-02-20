
cp ../slib/src/slib.h ./src
cp ../slib/build/slib.so ./build

cd build
gcc ../src/library.c ./slib.so -o ./library
