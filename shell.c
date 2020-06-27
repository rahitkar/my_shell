#include <stdio.h>
#include <unistd.h>   //fork exac
#include <sys/wait.h> //wait
#include <string.h>   //string
#include <signal.h>   //signal
#include <fcntl.h>    //open

#include "config.h"
#include "parse.h"
#include "print_prompt.h"
#include "builtin.h"
#include "linked_list.h"
#include "exec_call.h"
#include "script.h"

typedef char *Char_ptr;

int main(void)
{
  List_ptr alias_list = create_list();

  int process_flag = 0;
  int rshrc_fd = open("/Users/step14/.rshrc", O_RDWR);
  char rsh_conttents[1000];
  read(rshrc_fd, rsh_conttents, 1000);

  run_script(rsh_conttents, alias_list, &process_flag);

  Char_ptr prompt_ditels = strcmp(prompt, "") == 0 ? "my_shell" : prompt; // check for configuration

  char command[300];
  char current_directory[100];
  int redirected_flag;
  // int process_flag = 0;
  while (1) // infinity loop to continue the shell
  {
    signal(SIGINT, SIG_IGN);                                                                         // quit ignored
    print_prompt(prompt_ditels, current_directory, process_flag, prmt_colour_flag, pwd_colour_flag); // print prompt as par the last status code
    gets(command);                                                                                   // get user command

    if (!strcmp(command, "exit")) // exit gracefully
      return 0;

    Char_ptr *args = split(command, " ");

    if (!strcmp(args[0], "run"))
    {
      char file_content[1000];
      int file_fd = open(args[1], O_RDWR);
      read(file_fd, file_content, 1000);
      run_script(file_content, alias_list, &process_flag);
      continue;
    }

    if (handle_builtin(args, command, alias_list, &process_flag))
    {
      continue;
    }
    int pid = execute_exec_commands(args);
    printf("\n");
    process_flag = WEXITSTATUS(pid); //status flag of process
  }
}