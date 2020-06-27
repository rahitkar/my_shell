#include <stdlib.h>

#include "script.h"
#include "builtin.h"
#include "exec_call.h"


void run_script(Char_ptr commands, List_ptr alias_list, int* process_flag)
{
  Char_ptr *file_commands = split(commands, "\n");

  int i = 0;
  while (file_commands[i] != NULL)
  {
    Char_ptr *command = split(file_commands[i], " ");

    if (handle_builtin(command, file_commands[i], alias_list, process_flag))
    {
      i++;
      continue;
    }
    int pid = execute_exec_commands(command);
    i++;
  }
}