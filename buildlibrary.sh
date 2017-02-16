
cp ../slib/src/slib.h ./src
cp ../slib/src/slib.so ./build

cd build
gcc ../src/library.c ./slib.so -o ./library