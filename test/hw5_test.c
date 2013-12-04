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
  int myerrno = cow_copy("/data/local/tmp/hw5_test", "/data/test");
  char *errmsg = strerror(myerrno);
  printf("%s\nNumber: %d\n", errmsg, myerrno);
  return 0;
}
