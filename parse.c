#include "parse.h"

int get_args_length(Char_ptr *args)
{
  size_t indx = 0;
  while (args[indx] != NULL)
  {
    indx++;
  }
  return indx;
}

Char_ptr copy_text(Char_ptr text)
{
  int length = strlen(text);
  Char_ptr copy = calloc(length + 1, sizeof(char));
  for (size_t i = 0; i < length + 1; i++)
  {
    copy[i] = text[i];
  }
  return copy;
}

Char_ptr *split(Char_ptr text, Char_ptr symbol)
{
  Char_ptr copy = copy_text(text);
  int counter = 0;
  Char_ptr *text_array_ptr = calloc(counter + 1, sizeof(Char_ptr));
  text_array_ptr[counter] = &copy[0];

  for (int i = 0; copy[i] != '\0'; i++)
  {
    if (copy[i] == symbol[0])
    {
      copy[i] = '\0';
      counter++;
      text_array_ptr = realloc(text_array_ptr, (counter + 1) * sizeof(Char_ptr));
      text_array_ptr[counter] = &copy[++i];
    }
  }
  counter++;
  text_array_ptr = realloc(text_array_ptr, (counter + 1) * sizeof(Char_ptr));
  text_array_ptr[counter] = NULL;
  return text_array_ptr;
}

unsigned long count_length(char *text)
{
  int count;
  for (count = 0; text[count] != '\0'; count++)
    ;
  return count;
}

Char_ptr join(char *text1, char *text2)
{
  unsigned long text1_length = count_length(text1);
  unsigned long text2_length = count_length(text2);

  char *joined_string = malloc((text1_length + text2_length + 1) * sizeof(char));

  int j = 0;
  for (unsigned long i = 0; i < text1_length + text2_length; i++)
  {
    if (i < text1_length)
    {
      joined_string[i] = text1[i];
    }
    else
    {
      joined_string[i] = text2[j];
      j++;
    }
  }
  return joined_string;
}

Char_ptr make_new_command(Char_ptr command, Char_ptr *args, int starting_indx, Char_ptr symbal)
{
  Char_ptr new_command = "";
  new_command = join(new_command, command);
  int i = starting_indx;
  while (args[i] != NULL)
  {
    new_command = join(new_command, args[i]);
    new_command = join(new_command, symbal);
    i++;
  }
  new_command[strlen(new_command) - 1] = '\0';
  return new_command;
}