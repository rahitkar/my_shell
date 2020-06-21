#include <stdlib.h>
#include <string.h>

#include "parse.h"

Char_ptr copy_text(Char_ptr text) {
  int length = strlen(text);
  Char_ptr copy = calloc(length, sizeof(char));
  for (size_t i = 0; i < length; i++)
  {
    copy[i] = text[i];
  }
  return copy;
}

Char_ptr *split(Char_ptr text, Char_ptr symbol)
{
  Char_ptr copy = copy_text(text);
  int counter = 0;
  Char_ptr *text_array_ptr = calloc(counter + 1, sizeof(Char_ptr ));
  text_array_ptr[counter] = &copy[0];

  for (int i = 0; copy[i] != '\0'; i++)
  {
    if (copy[i] == symbol[0])
    {
      copy[i] = '\0';
      counter++;
      text_array_ptr = realloc(text_array_ptr, (counter + 1) * sizeof(Char_ptr ));
      text_array_ptr[counter] = &copy[++i];
    }
  }
  text_array_ptr = realloc(text_array_ptr, (counter + 1) * sizeof(Char_ptr ));
  counter++;
  text_array_ptr[counter] = NULL;
  return text_array_ptr;
}