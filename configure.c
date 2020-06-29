#include "configure.h"

void configure()
{
  char path[200] = "/Users/", file_path_from_home[] = "/shell/configure.js";
  char *user = getenv("USER");
  strcat(path, user);
  strcat(path, file_path_from_home);
  
  int pid = fork();
  if (pid == 0)
  {
    execlp("node", "node", path, NULL);
    printf("file not found\n");
    exit(-1);
  }
  else
  {
    wait(&pid);
  }
  return;
}