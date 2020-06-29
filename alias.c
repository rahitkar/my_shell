#include "alias.h"

/*
alias a = ls //set alias ["alias", "a", "=", "ls"]
alias // display
unalias 
*/

int is_command_alias(Char_ptr* args, List_ptr alias_list)
{
  return search(alias_list, args[0]) > -1
   ? 1 : 0;
}

int handle_alias(Char_ptr* args, List_ptr alias_list)
{
  int length = get_args_length(args);
  if (length == 1)
  {
    display(alias_list);
    return 0;
  }

  if (length <= 3)
  {
    fprintf( stderr, "rsh: not enough arguments\n");
    return -1;
  }
  
  if (!strcmp("=", args[2]))
  {
    Char_ptr aliashed_command = "";
    aliashed_command = make_new_command(aliashed_command, args, 3, " ");
    add_to_end(alias_list, aliashed_command, args[1]);
  }
  return 0;
}

// [a, dir, NULL] [ls, dir, NULL]

Char_ptr get_alished_command(Char_ptr command, List_ptr alias_list) {
  int position = 0;
  Node_ptr iterator = alias_list->head;
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

Char_ptr* perform_alias(Char_ptr* args, List_ptr alias_list)
{
  Char_ptr alished_command = get_alished_command(args[0], alias_list);
  alished_command = join(alished_command, " ");
  Char_ptr joined_command = make_new_command(alished_command, args, 1, " ");
  Char_ptr* actual_command = split(joined_command, " ");
  return actual_command;
}

int handle_unalias(Char_ptr* args, List_ptr alias_list)
{
  if (get_args_length(args) < 2)
  {
    fprintf(stderr, "rsh: unalias: not enough arguments\n");
    return -1;
  }
  
  int position = search(alias_list, args[1]);
  if (remove_at(alias_list, position))
  {
    return 0;
  }
  fprintf(stderr, "rsh: unalias: no such element: %s\n", args[1]);
  return -1;
}