#! /bin/bash
rm -rf *.o
gcc -c *.c
gcc -o $1 *.o
rm -rf *.o
./$1
rm $1
