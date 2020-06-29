#include "exec_call.h"

int execute_exec_commands(Char_ptr *args, int* process_flag)
{
  int pid = fork();
  if (pid == 0)
  {
    signal(SIGINT, NULL); 
    execvp(args[0], args);
    fprintf(stderr, "rsh: %s commad not found\n", args[0]); 
    exit(-1);
  }
  else 
  {
    wait(&pid);
  }
  *process_flag = WEXITSTATUS(pid);
  return 0;
}
