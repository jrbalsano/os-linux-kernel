#ifndef __LOCK_H_
#define __LOCK_H_

#include <sys/syscall.h>

#define __COW_COPY 378 

inline long cow_copy(char *src, char *dest) {
  return syscall(__COW_COPY, src, dest);
}


#endif  // __LOCK_H_
