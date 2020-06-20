#include <stdio.h>
#include <unistd.h>

#include "print_prompt.h"

void red()
{
  printf("\033[1;31m");
}

void yellow()
{
  printf("\033[1;33m");
}

void blue()
{
  printf("\033[1;34m");
}

void green()
{
  printf("\033[0;32m");
}

void reset()
{
  printf("\033[0m");
}

void print_prompt(char *shell_ditels, char *current_directory, int flag)
{
  yellow();
  printf("%s", shell_ditels);
  blue();
  printf("%s", getcwd(current_directory, 100));
  if (flag)
  {
    red();
    printf("-> ");
    reset();
    return;
  }
  green();
  printf("-> ");
  reset();
}