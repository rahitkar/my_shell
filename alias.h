#ifndef __ALIAS_H_
#define __ALIAS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "linked_list.h"
#include "parse.h"

int handle_alias(Char_ptr* args, List_ptr list);

int is_command_alias(Char_ptr* args, List_ptr alias_list);

Char_ptr* perform_alias(Char_ptr* args, List_ptr alias_list);

int handle_unalias(Char_ptr* args, List_ptr alias_list);

#endif