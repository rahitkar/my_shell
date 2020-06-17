#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

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
  char current_directory[100];
  while (1)
  {
    signal(SIGINT, SIG_IGN);
    printf("%s_$%s-> ", shell_ditels, getcwd(current_directory, 100));
    gets(command);
    if (!strcmp(command, "exit"))
      return 0;

    Char_ptr *args = split(command, " ");
    if (!strcmp(args[0], "..")) //builtIn commands
    {
      chdir(args[0]);
      continue;
    }

    if (!strcmp(args[0], "cd"))
    {
      getcwd(current_directory, 100);
      char *dir = strcat(current_directory, "/");
      chdir(strcat(dir, args[1]));
      continue;
    }

    int pid = fork(); // exac part
    if (pid == 0)
    {
      signal(SIGINT, NULL);
      execvp(args[0], args);
      printf("commad not found\n");
      exit(-1);
    }
    else
    {
      wait(&pid);
    }
    printf("\n");
  }
}