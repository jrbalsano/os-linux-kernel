#include <linux/compiler.h>
#include <linux/sched.h>

//not sure if these includes will work
#include <linux/fs.h>
#include "internal.h"

asmlinkage int sys_ext4_cowcopy(const char __user *src, const char __user *dest) {

  struct file * myFile = filp_open(src, O_RDONLY, 0644);

  
  //if path is not null, check to see if the same as the src
  if(file.path){
    char *myPath = &file.path;
    char *srcPointer = src;

    int validPath = 1;
    while(myPath){
	if(*myPath != *srcPointer){
		validPath=0;
		break;
	}

	myPath++;
	srcPointer++;
    }

    if(!validPath){
	return -1; //change this to the proper error
    }

    //now check device

  } 


  return 0;
}
