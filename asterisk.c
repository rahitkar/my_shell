#include "asterisk.h"

int is_asterisk(Char_ptr commands)
{
  int i = 0;
  while (commands[i] != '\0')
  {
    if (commands[i] == '*')
    {
      return 1;
    }
    i++;
  }
  return 0;
} // might be a repetition

Char_ptr create_command(Char_ptr *args, Char_ptr input)
{
  Char_ptr new_commands = join(args[0], "\n");
  new_commands = join(new_commands, input);
  new_commands = make_new_command(new_commands, args, 2, "\n");
  return new_commands;
}

Char_ptr *handle_asterisk(Char_ptr *args)
{
  Char_ptr *expanded_commands = args;
  int flag = 0;
  Char_ptr suppoting_commands[] = {"ls", ">", "out", NULL};

  handle_redirection(suppoting_commands, ">", &flag);

  int pid = fork();
  if (pid == 0)
  {
    execlp("node", "node", "/Users/step14/shell/wildcard.js", args[1], NULL);
  }
  else
  {
    wait(&pid);
    char input[10000];
    int fd = open("out", O_RDONLY);
    read(fd, input, 10000);
    close(fd);

    if (!strcmp(args[0], "ls"))
    {
      printf("%s", input);
      return expanded_commands;
    }

    Char_ptr new_commands = create_command(args, input);
    Char_ptr *expanded_commands = split(new_commands, "\n");
    return expanded_commands;
  }
  return expanded_commands;
}