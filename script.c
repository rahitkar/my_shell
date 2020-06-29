#include "script.h"
#include "alias.h"
#include "set_variable.h"

void run_script(Char_ptr commands, List_ptr alias_list, List_ptr variable_list, int *process_flag)
{
  Char_ptr *file_commands = split(commands, "\n");
  file_commands[get_args_length(file_commands) -1] = NULL;
  
  int i = 0;
  while (file_commands[i] != NULL)
  {
    Char_ptr *command = split(file_commands[i], " ");

    if (is_command_alias(command, alias_list))
    {
      command = perform_alias(command, alias_list);
    }

    if (is_perform_variable(command))
    {
      perform_variable(command, variable_list);
    }

    if (handle_builtin(command, file_commands[i], alias_list, variable_list, process_flag))
    {
      i++;
      continue;
    }
    if (!strcmp(command[0], "run"))
    {
      char file_content[1000];
      int file_fd = open(command[1], O_RDWR);
      read(file_fd, file_content, 1000);
      run_script(file_content, alias_list, variable_list, process_flag);
      i++;
      continue;
    }
    execute_exec_commands(command, process_flag);
    i++;
  }
}