#ifndef __REDIRECT_H_
#define __REDIRECT_H_

#include "parse.h"

typedef struct
{
  Char_ptr *parsed_args;
  int index_of_file;
} Args_info;

typedef Args_info *Args_info_ptr;

int is_redirected(Char_ptr *args);

void handle_redirection(Char_ptr *args, Char_ptr type, int* process_flag);

#endif