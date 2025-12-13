#define NIB_IMPLEMENTATION
#define ANSI_ENABLE
#include "../build/nib.h"


int main()
{
  CMD cmd = { 0 };
  nib_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", "-std=c99", "-o", "./example", "./example.c", "-lm");
  if(!nib_cmd_run(cmd)) return 1;
  return 0;
}
