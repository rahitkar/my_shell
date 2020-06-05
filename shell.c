#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

typedef char *Char_ptr;

Char_ptr *split(char *text, char *symbol)
{
  int counter = 0;
  Char_ptr* text_array_ptr = calloc(counter + 1, sizeof(char *));
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
  char command[300];

  printf("my_shell_$-> ");
  while (1)
  {
    gets(command);

    if (!strcmp(command, "exit"))
    {
      return 0;
    }
    
    // Char_ptr args[] = {command, NULL};
    Char_ptr* args = split(command, " ");
    int pid = fork();
    if (pid == 0)
    {
      // printf("child%d\n", pid);
      execvp(args[0], args);
      printf("commad not found\n");
      return 1;
    }
    else
    {
      wait(&pid);
      // printf("parent%d\n", pid);
    }
    printf("my_shell_$-> ");
  }
}