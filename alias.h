#ifndef __ALIAS_H_
#define __ALIAS_H_

#include "linked_list.h"
typedef char* Char_ptr;

int handle_alias(Char_ptr* args, List_ptr list);

int is_command_alias(Char_ptr* args, List_ptr alias_list);

int perform_alias(Char_ptr* args, List_ptr alias_list);

int handle_unalias(Char_ptr* args, List_ptr alias_list);

#endif