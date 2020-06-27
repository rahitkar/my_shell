#ifndef __PARSE_H_
#define __PARSE_H_

typedef char *Char_ptr;
Char_ptr *split(char *text, char *symbol);
Char_ptr join(char *text1, char *text2);
int get_args_length(Char_ptr* args);

#endif