#ifndef __BUILTIN_H_
#define __BUILTIN_H_

#include "linked_list.h"

typedef char* Char_ptr;
 
int handle_builtin(Char_ptr* args, Char_ptr commad, List_ptr alias_list, int* process_flag);

#endif