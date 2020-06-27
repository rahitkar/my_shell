#include <stdio.h>
#include <stdlib.h>   //exit
#include <unistd.h>   //fork exac
#include <sys/wait.h> //wait
#include <signal.h>   //signal

#include "exec_call.h"

int execute_exec_commands(Char_ptr *args)
{
  int pid = fork(); // creating two processes
  if (pid == 0)     //child
  {
    signal(SIGINT, NULL);                                   //quit signal redstored
    execvp(args[0], args);                                  // changing the process img with the given command
    fprintf(stderr, "rsh: %s commad not found\n", args[0]); // if exec fails then it comes here else not
    exit(-1);                                               //come out with fail exit code
  }
  else //parent
  {
    wait(&pid); // wait for the child to finish the process
  }
  return 0;
}