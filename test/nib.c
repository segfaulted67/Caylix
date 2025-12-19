#define NIB_IMPLEMENTATION
#define ANSI_ENABLE
#include "../build/nib.h"

static char *CC = "cc";

int main(int argc, char **argv)
{
  CMD cmd = { 0 };
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "clean") == 0) {
      nib_cmd_append(&cmd, "rm", "ode_test", "fft_test");
    }
		else if (strcmp(argv[i], "fft") == 0) {
		nib_cmd_append(&cmd, CC, "-Wall", "-Wextra", "-std=c99", "-o", "./fft_test", "./fft_test.c", "-lm");
		}
		else if (strcmp(argv[i], "ode") == 0) {
		nib_cmd_append(&cmd, CC, "-Wall", "-Wextra", "-std=c99", "-o", "./ode_test", "./ode_test.c", "-lm");
		}
  }
  if(!nib_cmd_run(cmd)) return 1;
  return 0;
}
