#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "alias.h"
#include "linked_list.h"

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

int get_length(Char_ptr* args)
{
  size_t indx = 0;
  while (args[indx] != NULL)
  {
    indx++;
  }
  return indx;
}

void handle_alias(Char_ptr* args, List_ptr alias_list)
{
  if (get_length(args) >= 3 && !strcmp("=", args[2]))
  {
    add_to_end(alias_list, args[3], args[1]);
    return;
  }
  display(alias_list);
}

// [a, dir, NULL] [ls, dir, NULL]

Char_ptr get_actual_command(Char_ptr command, List_ptr alias_list) {
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

void perform_alias(Char_ptr* args, List_ptr alias_list)
{
  Char_ptr command = get_actual_command(args[0], alias_list); 
  args[0] = command;
  int pid = fork();
  if (pid == 0)
  {
  execvp(args[0], args);
  exit(-1);
  } else
  {
    wait(&pid);
  }
}

void handle_unalias(Char_ptr* args, List_ptr alias_list)
{
  if (get_length(args) < 2)
  {
    printf("unalias: not enough arguments\n");
    return;
  }
  
  int position = search(alias_list, args[1]);
  if (remove_at(alias_list, position))
  {
    return;
  }
  printf("unalias: no such element: %s\n", args[1]);
}
