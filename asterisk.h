#ifndef __ASTERISK_H_
#define __ASTERISK_H_

typedef char* Char_ptr;

int is_asterisk(Char_ptr commands);

Char_ptr* handle_asterisk(Char_ptr* args);

#endif