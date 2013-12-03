#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <signal.h>
#include "cowcopy.h"

int main(int argc, char **argv) {

  char *errmsg = strerror(cow_copy());
  printf("%s\n", errmsg);
  return 0;
}
