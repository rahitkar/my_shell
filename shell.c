#include <stdio.h>
#include <stdlib.h>   //getenv
#include <unistd.h>   //fork exac read
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
#include "alias.h"
#include "set_variable.h"
#include "asterisk.h"

typedef char *Char_ptr;

int main(void)
{
  List_ptr alias_list = create_list();
  List_ptr variable_list = create_list();

  int process_flag = 0;
  char rsh_path[30] = "/Users/", rsh_name[] = "/shell/.rshrc";
  char *user = getenv("USER");
  strcat(rsh_path, user);
  strcat(rsh_path, rsh_name);
  int rshrc_fd = open(rsh_path, O_RDWR);
  char rsh_conttents[1000];
  read(rshrc_fd, rsh_conttents, 1000);

  run_script(rsh_conttents, alias_list, variable_list, &process_flag);

  Char_ptr prompt_ditels = strcmp(prompt, "") == 0 ? "my_shell" : prompt; // check for configuration

  char command[300];
  char current_directory[100];
  int redirected_flag;
  while (1) // infinity loop to continue the shell
  {
    signal(SIGINT, SIG_IGN); // quit ignored

    print_prompt(prompt_ditels, current_directory, process_flag, prmt_colour_flag, pwd_colour_flag); // print prompt as par the last status code
    gets(command);

    if (!strcmp(command, "exit")) // exit gracefully
      return 0;

    Char_ptr *args = split(command, " ");

    if (is_asterisk(command))
    {
      args = handle_asterisk(args);
      if (!strcmp(args[0], "ls"))
      {
        continue;
      }
    }

    if (is_command_alias(args, alias_list))
    {
      args = perform_alias(args, alias_list);
    }

    if (is_perform_variable(args))
    {
      perform_variable(args, variable_list);
    }

    if (!strcmp(args[0], "run"))
    {
      char file_content[1000];
      int file_fd = open(args[1], O_RDWR);
      read(file_fd, file_content, 1000);
      run_script(file_content, alias_list, variable_list, &process_flag);
      continue;
    }

    if (handle_builtin(args, command, alias_list, variable_list, &process_flag))
    {
      continue;
    }

    execute_exec_commands(args, &process_flag);
  }
}