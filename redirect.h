#ifndef __REDIRECT_H_
#define __REDIRECT_H_

typedef char *Char_ptr;

int is_redirected(Char_ptr *args);

void handle_redirection(Char_ptr *args, Char_ptr type, int* process_flag);

#endif