#ifndef __PIPE_H_
#define __PIPE_H_

typedef char *Char_ptr;

typedef struct
{
  Char_ptr** commands;
  int length;
} Commands_info;

int is_piped(Char_ptr command);

void handle_pipes(Char_ptr command);

#endif