#define NIB_IMPLEMENTATION
#define ANSI_ENABLE
#include "../build/nib.h"


int main(int argc, char **argv)
{
  CMD cmd = { 0 };
  if(argc == 1) {
    nib_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-std=c99", "-o", "./example", "./example.c", "-lm");
  }
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "clean") == 0) {
      nib_cmd_append(&cmd, "rm", "example");
    }
    else if (strcmp(argv[i], "build") == 0) {
      nib_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", "-std=c99", "-o", "./example", "./example.c", "-lm");
    }
    else if (strcmp(argv[i], "clang") == 0) {
      nib_cmd_append(&cmd, "clang", "-Wall", "-Wextra", "-std=c99", "-o", "./example", "./example.c", "-lm");
    }
  }
  if(!nib_cmd_run(cmd)) return 1;
  return 0;
}
