#! /bin/bash
rm -rf *.o
gcc -c *.c
gcc -o $1 *.o
rm -rf *.o
rm ~/bin/$1
cp ./$1 ~/bin
~/$1