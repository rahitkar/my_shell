#include <stdio.h>
#include <stdlib.h>   //exit
#include <unistd.h>   //fork exac
#include <sys/wait.h> //wait
#include <string.h>   //string
#include <signal.h>   //signal

#include "config.h"
#include "parse.h"
#include "print_prompt.h"
#include "builtin.h"
#include "linked_list.h"

typedef char *Char_ptr;

int main(void)
{
  List_ptr alias_list = create_list();
  
  Char_ptr prompt_ditels = strcmp(prompt, "") == 0 ? "my_shell" : prompt; // check for configuration

  char command[300];
  char current_directory[100];
  int redirected_flag;
  int process_flag = 0;
  while (1) // infinity loop to continue the shell
  {
    signal(SIGINT, SIG_IGN); // quit ignored
    print_prompt(prompt_ditels, current_directory, process_flag, prmt_colour_flag, pwd_colour_flag); // print prompt as par the last status code
    gets(command); // get user command

    if (!strcmp(command, "exit")) // exit gracefully
      return 0;

    Char_ptr *args = split(command, " ");

    if (handle_builtin(args, command, alias_list, &process_flag))
    {
      continue;
    }
    
    int pid = fork(); // creating two processes
    if (pid == 0)     //child
    {
      signal(SIGINT, NULL); //quit signal redstored
      execvp(args[0], args); // changing the process img with the given command
      printf("rsh:commad not found\n"); // if exec fails then it comes here else not
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
