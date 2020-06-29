#ifndef __PARSE_H_
#define __PARSE_H_

#include <stdio.h>
#include <stdlib.h>   //getenv exit
#include <unistd.h>   //fork dup exac read
#include <sys/wait.h> //wait
#include <string.h>   //string
#include <signal.h>   //signal
#include <fcntl.h>    //open

typedef char *Char_ptr;

Char_ptr *split(char *text, char *symbol);

Char_ptr join(char *text1, char *text2);

int get_args_length(Char_ptr* args);

Char_ptr make_new_command(Char_ptr command, Char_ptr *args, int starting_indx, Char_ptr symbal);

#endif