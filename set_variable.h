#ifndef __SET_VARIABLE_H_
#define __SET_VARIABLE_H_

#include "linked_list.h"

int handle_set_variable(Char_ptr* args, List_ptr variable_list);

int is_perform_variable(Char_ptr* args);

void perform_variable(Char_ptr* args, List_ptr variable_list);

int perform_unset_variable(Char_ptr* args, List_ptr variable_list);

#endif