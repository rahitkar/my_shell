#include <stdlib.h>

#include "parse.h"

Char_ptr *split(char *text, char *symbol)
{
  int counter = 0;
  Char_ptr *text_array_ptr = calloc(counter + 1, sizeof(char *));
  text_array_ptr[counter] = &text[0];

  for (int i = 0; text[i] != '\0'; i++)
  {
    if (text[i] == symbol[0])
    {
      text[i] = '\0';
      counter++;
      text_array_ptr = realloc(text_array_ptr, (counter + 1) * sizeof(char *));
      text_array_ptr[counter] = &text[++i];
    }
  }
  text_array_ptr = realloc(text_array_ptr, (counter + 1) * sizeof(char *));
  counter++;
  text_array_ptr[counter] = NULL;

  return text_array_ptr;
}