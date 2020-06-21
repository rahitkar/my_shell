#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

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