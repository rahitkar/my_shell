#ifndef __PARSE_H_
#define __PARSE_H_

#include <stdio.h>
#include <stdlib.h>   //getenv
#include <unistd.h>   //fork exac read
#include <sys/wait.h> //wait
#include <string.h>   //string
#include <signal.h>   //signal
#include <fcntl.h>    //open



typedef char *Char_ptr;
Char_ptr *split(char *text, char *symbol);
Char_ptr join(char *text1, char *text2);
int get_args_length(Char_ptr* args);

#endif