#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //fork exac
#include <sys/wait.h> //wait

#include "configure.h"

typedef char *Char_ptr;

void configure()
{
  int pid = fork();
  if (pid == 0)
  {
    execlp("node", "node", "configure.js", NULL);
    printf("file not found\n"); 
    exit(-1);
  } else
  {
    wait(&pid);
  }
  return;
}