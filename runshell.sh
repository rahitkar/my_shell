gcc -c ~/shell/*.c
gcc -o ~/bin/$1 *.o
rm *.o
~/bin/$1