#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <signal.h>
#include "cowcopy.h"
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv) {

  size_t test_desc = open("/data/local/tmp/test", O_WRONLY);
  write(test_desc, "POOP\n", 6);
  close(test_desc);

  int myerrno = cow_copy("/data/local/tmp/test", "/data/local/tmp/test_file1");
  char *errmsg = strerror(errno);
  printf("%s\nNumber: %d\n", errmsg, errno);

  myerrno = cow_copy("/data/local/tmp/test", "/data/local/tmp/test_file2");
  errmsg = strerror(errno);
  printf("%s\nNumber: %d\n", errmsg, errno);

  myerrno = cow_copy("/data/local/tmp/test", "/data/local/tmp/test_file3");
  errmsg = strerror(errno);
  printf("%s\nNumber: %d\n", errmsg, errno);

  /* printf("OPENING READ ONLY\n"); */
  /* size_t filedesc =  open("/data/local/tmp/test_file", O_WRONLY); */
  /* write(filedesc, "POOP", 5); */
  /* close(filedesc); */
  

  /* printf("OPENING WRITE ONLY\n"); */
  /* filedesc = open("/data/local/tmp/test_file", O_WRONLY); */
  /* close(filedesc); */
  


  /* printf("OPENING READ/WRITE\n"); */
  /* filedesc =  open("/data/local/tmp/test_file", O_RDWR); */
  /* close(filedesc); */


  return 0;
}
