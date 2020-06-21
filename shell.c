#include <stdio.h>
#include <stdlib.h>
// #include <sys/types.h>
#include <unistd.h> //fork exac
#include <sys/wait.h> //wait
#include <string.h> //string
#include <signal.h> //signal

#include "config.h"
#include "parse.h"
#include "print_prompt.h"
#include "redirect.h"

typedef char *Char_ptr;

int main(void)
{
  Char_ptr shell_ditels = strcmp(prompt, "") == 0 ? "my_shell" : prompt;
  char command[300];
  char current_directory[100];
  int process_flag = 0;
  int redirected_flag;
  while (1)
  {
    signal(SIGINT, SIG_IGN);
    print_prompt(shell_ditels, current_directory, process_flag);
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
    redirected_flag = is_redirected(args); //redirection
    if (redirected_flag)
    {
      char* type = ">>";
      if (redirected_flag == 1)
      {
        type = ">";
      }
      printf("%s", type);
      handle_redirection(args, type);
      continue;
    }

    int pid = fork(); // exac part
    if (pid == 0) //child
    {
      signal(SIGINT, NULL);
      execvp(args[0], args);
      printf("commad not found\n");
      exit(-1);
    }
    else //parent
    {
      wait(&pid);
    }
    printf("\n");
    process_flag = WEXITSTATUS(pid); //status flag of process
  }
}
