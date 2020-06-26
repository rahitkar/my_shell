#ifndef __ALIAS_H_
#define __ALIAS_H_

#include "linked_list.h"
typedef char* Char_ptr;

void handle_alias(Char_ptr* args, List_ptr list);

int is_command_alias(Char_ptr* args, List_ptr alias_list);

void perform_alias(Char_ptr* args, List_ptr alias_list);

Char_ptr get_actual_command(Char_ptr command, List_ptr alias_list);

void handle_unalias(Char_ptr* args, List_ptr alias_list);

#endif