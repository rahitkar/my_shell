#! /bin/bash
gcc -c ~/shell/*.c
gcc -o ~/bin/shell *.o
rm *.o
~/bin/shell