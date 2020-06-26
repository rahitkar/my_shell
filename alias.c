#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "alias.h"
#include "linked_list.h"
#include "parse.h"

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

int get_args_length(Char_ptr* args)
{
  size_t indx = 0;
  while (args[indx] != NULL)
  {
    indx++;
  }
  return indx;
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
    int i = 3;
    while (args[i] != NULL)
    {
      aliashed_command = join(aliashed_command, args[i]);
      aliashed_command = join(aliashed_command, " ");
      i++;
    }
    aliashed_command[strlen(aliashed_command) -1] = '\0';
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

Char_ptr make_command(Char_ptr command, Char_ptr* args)
{
  Char_ptr new_command = "";

  new_command = join(new_command, command);
  new_command = join(new_command, " ");

  int i = 1;
  while (args[i] != NULL)
  {
    new_command = join(new_command, args[i]);
    new_command = join(new_command, " ");
    i++;
  }
  new_command[strlen(new_command) -1] = '\0';
  return new_command;
}

int perform_alias(Char_ptr* args, List_ptr alias_list)
{
  Char_ptr alished_command = get_alished_command(args[0], alias_list);
  Char_ptr joined_command = make_command(alished_command, args);
  Char_ptr* actual_command = split(joined_command, " ");
  int pid = fork();
  if (pid == 0)
  {
  execvp(actual_command[0], actual_command);
  fprintf( stderr, "rsh: aliased command: %s not found\n", actual_command[0]);
  return 1;
  } else
  {
    wait(&pid);
  }
  return 0;
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
