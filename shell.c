#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //fork exac
#include <sys/wait.h> //wait
#include <string.h>   //string
#include <signal.h>   //signal

#include "config.h"
#include "parse.h"
#include "print_prompt.h"
#include "redirect.h"
#include "configure.h"

typedef char *Char_ptr;

int main(void)
{
  Char_ptr prompt_ditels = strcmp(prompt, "") == 0 ? "my_shell" : prompt; // check for configuration

  char command[300];
  char current_directory[100];
  int process_flag = 0;
  int redirected_flag;
  while (1) // infinity loop to continue the shell
  {
    signal(SIGINT, SIG_IGN); // quit ignored
    print_prompt(prompt_ditels, current_directory, process_flag, prmt_colour_flag, pwd_colour_flag); // print prompt as par the last status code
    gets(command); // get user command

    if (!strcmp(command, "exit")) // exit gracefully
      return 0;

    Char_ptr *args = split(command, " ");

    if (!strcmp(args[0], ".config")) //builtIn commands
    {
      configure();
      execlp("runshell.sh", "runshell.sh", "shell", NULL);
      continue;
    }

    if (!strcmp(args[0], ".."))
    {
      chdir(args[0]);
      continue;
    }

    if (!strcmp(args[0], "cd"))
    {
      getcwd(current_directory, 100); // get current working directory
      char *dir = strcat(current_directory, "/"); //concat to make path
      chdir(strcat(dir, args[1])); // change directory
      continue;
    }
    redirected_flag = is_redirected(args); //redirection check
    if (redirected_flag)
    {
      Char_ptr type = ">>";
      if (redirected_flag == 1)
      {
        type = ">";
      }
      handle_redirection(args, type);
      continue;
    }

    int pid = fork(); // creating two processes
    if (pid == 0)     //child
    {
      signal(SIGINT, NULL); //quit signal redstored
      execvp(args[0], args); // changing the process img with the given command
      printf("commad not found\n"); // if exec fails then it comes here else not
      exit(-1); //come out with fail exit code
    }
    else //parent
    {
      wait(&pid); // wait for the child to finish the process
    }
    printf("\n");
    process_flag = WEXITSTATUS(pid); //status flag of process
  }
}
