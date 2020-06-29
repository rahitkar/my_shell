#include "set_variable.h"

int handle_set_variable(Char_ptr* args, List_ptr variable_list)
{
  if (get_args_length(args) <= 2)
  {
    fprintf( stderr, "rsh: not enough arguments\n");
    return -1;
  }
    Char_ptr variable_command = "";
    variable_command = make_new_command(variable_command, args, 2, " ");
    add_to_end(variable_list, variable_command, args[0]);
  return 0;
}

int is_perform_variable(Char_ptr* args)
{
  int i = 0;
  while (args[i] != NULL)
  {
    if (args[i][0] == '$')
    {
      return 1;
    }
    i++;
  }
  return 0;
}

Char_ptr get_variable_command(Char_ptr command, List_ptr variable_list) {
  int position = 0;
  Node_ptr iterator = variable_list->head;
  while (iterator != NULL)
  {
    if (!strcmp(command, iterator->alias))
    {
      return iterator->command;
    }
    position++;
    iterator = iterator->next;
  }
  return "wrong command";
}

int get_varable_command_index(Char_ptr* args)
{
  int i = 0;
  while (args[i] != NULL)
  {
    if (args[i][0] == '$')
    {
      return i;
    }
    i++;
  }
  return -1;
}

void perform_variable(Char_ptr* args, List_ptr variable_list)
{
  int variable_command_indx = get_varable_command_index(args);
  Char_ptr* command = split(args[variable_command_indx], "$");
  Char_ptr variable_command = get_variable_command(command[1] , variable_list);
  args[variable_command_indx] = variable_command;
}

int perform_unset_variable(Char_ptr* args, List_ptr variable_list)
{
  if (get_args_length(args) <= 1)
  {
    fprintf(stderr, "rsh: Not enough arguments\n");
    return -1;
  }
  int element_index = search(variable_list, args[1]);
  return !remove_at(variable_list, element_index);
}