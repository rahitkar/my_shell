#ifndef __SCRIPT_H_
#define __SCRIPT_H_

#include "parse.h"
#include "linked_list.h"

void run_script(Char_ptr commands, List_ptr alias_list, List_ptr variable_list, int *process_flag);

#endif