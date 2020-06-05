#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

typedef char *Char_ptr;

int main(void)
{
  char command[300];

  printf("my_shell_$-> ");
  while (1)
  {
    gets(command);
    if (!strcmp(command, "exit"))
    {
      return 1;
    }
    
    printf("my_shell_$-> ");
    Char_ptr args[] = {command, NULL};
    int pid = fork();
    if (pid == 0)
    {
      execvp(command, args);
    }
    else
    {
      wait(&pid);
    }
  }
}