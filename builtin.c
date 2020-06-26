#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "builtin.h"
#include "redirect.h"
#include "configure.h"
#include "pipe.h"
#include "alias.h"
#include "script.h"

int handle_builtin(Char_ptr *args, Char_ptr command, List_ptr alias_list)
{
  char current_directory[100];
  int redirected_flag;

  if (is_command_alias(args, alias_list))
  {
    printf("aliashed command\n");
    perform_alias(args, alias_list);
    return 1;
  }

  if (!strcmp("alias", args[0]))
  {
    handle_alias(args, alias_list);
    return 1;
  }

  if (!strcmp(args[0], "unalias"))
  {
    handle_unalias(args, alias_list);
    return 1;
  }

  // if (is_script(command))
  // {
  //   printf("script\n");
  //   // handle_script(command);
  //   return 1;
  // } will implement later

  if (!strcmp(args[0], ".config")) //builtIn commands
  {
    configure();
    execlp("runshell.sh", "runshell.sh", "shell", NULL);
    return 1;
  }

  if (!strcmp(args[0], ".."))
  {
    chdir(args[0]);
    return 1;
  }

  if (!strcmp(args[0], "cd"))
  {
    getcwd(current_directory, 100);             // get current working directory
    char *dir = strcat(current_directory, "/"); //concat to make path
    chdir(strcat(dir, args[1]));                // change directory
    return 1;
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
    return 1;
  }

  if (is_piped(command))
  {
    handle_pipes(command);
    return 1;
  }
  return 0;
}
