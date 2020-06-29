#ifndef __ASTERISK_H_
#define __ASTERISK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //fork exac read
#include <sys/wait.h> //wait
#include <fcntl.h>    //open
#include <string.h>

#include "redirect.h"
#include "parse.h"

typedef char* Char_ptr;

int is_asterisk(Char_ptr commands);

Char_ptr* handle_asterisk(Char_ptr* args);

#endif