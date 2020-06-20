#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "config.h"
#include "parse.h"
#include "print_prompt.h"

typedef char *Char_ptr;

int is_redirected(Char_ptr command) {
  
  int i = 0;

  while (command[i] != '\0')
  {
    if(command[i] == '>') {
      return 1;
    }
    i++;
  }
  return 0;
}

int main(void)
{
  Char_ptr shell_ditels = strcmp(prompt, "") == 0 ? "my_shell" : prompt;
  char command[300];
  char current_directory[100];
  int flag = 0;
  while (1)
  {
    signal(SIGINT, SIG_IGN);
    print_prompt(shell_ditels, current_directory, flag);
    gets(command);
    if (is_redirected(command))
    {
      printf("redirected");
      continue;
    }

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
    flag = WEXITSTATUS(pid);
  }
}