#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

typedef char *Char_ptr;

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

int main(void)
{
  Char_ptr shell_ditels = strcmp(prompt, "") == 0 ? "my_shell" : prompt;
  
  char command[300];
  printf("%s_$-> ", shell_ditels);
  while (1)
  {
    gets(command);
    if (!strcmp(command, "exit"))
    {
      return 0;
    }
    Char_ptr *args = split(command, " ");
    int pid = fork();
    if (pid == 0)
    {
      execvp(args[0], args);
      printf("commad not found\n");
    }
    else
    {
      wait(&pid);
    }
  printf("%s_$-> ", shell_ditels);
  }
}