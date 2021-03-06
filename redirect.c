#include "redirect.h"

int is_redirected(Char_ptr *args)
{
  for (size_t i = 0; args[i] != NULL; i++)
  {
    for (size_t j = 0; args[i][j] != '\0'; j++)
    {
      if (args[i][j] == '>' && args[i][j + 1 ] == '>') // cheking >>
      {
        return 2;
      }
      if (args[i][j] == '>')
      {
        return 1;
      }
    }
  }
  return 0;
}

Args_info_ptr parse_args(Char_ptr *args, Char_ptr type)
{
  Args_info_ptr args_info = calloc(1, sizeof(Args_info));
  Char_ptr *list_of_args = calloc(20, sizeof(Char_ptr));
  int i = 0;
  while (args[i] != NULL)
  {
    if (!strcmp(args[i], type))
    {
      list_of_args[i] = NULL;
      i++;
      args_info->index_of_file = i;
    }
    list_of_args[i] = args[i];
    i++;
  }
  args_info->parsed_args = list_of_args;
  return args_info;
}

void handle_redirection(Char_ptr *args, Char_ptr type, int* process_flag)
{
  Args_info_ptr separeted_args = parse_args(args, type);
  int file_index = separeted_args->index_of_file;
  int out, savestdin_stream, savestdout_stream;
  if (!strcmp(">", type))
  {
    out = open(separeted_args->parsed_args[file_index], O_RDWR | O_CREAT | O_TRUNC, 0666);
  }
  else
  {
    out = open(separeted_args->parsed_args[file_index], O_RDWR | O_APPEND);
  }
  savestdout_stream = dup(1);
  dup2(out, 1);
  close(out);
  int pid = fork();
  if (pid == 0)
  {
    execvp(separeted_args->parsed_args[0], separeted_args->parsed_args);
    *process_flag = -1;
    fprintf(stderr, "rsh: %s command not found\n", separeted_args->parsed_args[0]);
    exit(-1);
  }
  else
  {
    wait(&pid);
    dup2(savestdout_stream, 1);
    *process_flag = WEXITSTATUS(pid);
  }
}