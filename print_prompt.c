#include "print_prompt.h"

typedef void (*Paint)();

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

void print_prompt(char *shell_ditels, char *current_directory, int flag, int prmt_cf, int pwd_cf)
{
  Paint colours[] = {red, yellow, blue, green, reset};
  colours[prmt_cf]();
  printf("%s", shell_ditels);
  colours[pwd_cf]();
  printf("%s", getcwd(current_directory, 100));
  green();
  if (flag)
  {
    red();
  }
  printf(" ❯ ");
  reset();
}