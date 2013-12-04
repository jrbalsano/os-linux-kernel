#include <linux/compiler.h>
#include <linux/sched.h>


#include <linux/string.h>
#include <linux/mm.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/fsnotify.h>
#include <linux/module.h>
#include <linux/tty.h>
#include <linux/namei.h>
#include <linux/backing-dev.h>
#include <linux/capability.h>
#include <linux/securebits.h>
#include <linux/security.h>
#include <linux/mount.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/personality.h>
#include <linux/pagemap.h>
#include <linux/syscalls.h>
#include <linux/rcupdate.h>
#include <linux/audit.h>
#include <linux/falloc.h>
#include <linux/fs_struct.h>
#include <linux/ima.h>
#include <linux/dnotify.h>
#include <linux/stat.h>

asmlinkage int sys_ext4_cowcopy(const char __user *src, const char __user *dest) {

  /* struct file * myFile = filp_open(src, O_RDONLY, 0644); */
  
  struct path pt; //path for src
  struct path destpt; //path for dest
  int error;
  char *safe_src = getname(src);
  printk("%s\n", safe_name);
  error = user_path_at(0, src, 0, &pt);
  if(!error){
    printk("\n\nChecking for errors\n\n");
    // Check if file is a directory or not
    if(!S_ISREG(pt.dentry->d_inode->i_mode)){
      printk("\n\nCHECKING IF IT'S DIRECTORY\n\n");
      return (-EPERM);
    }
    printk("Passed all tests\n");
  }
  else{
    return error;
  }

  //check for same filesystem by comparing mount
  
  // Separate filename from path
  char *src_filename_start = strrchr(safe_src, '/') + 1;
  char *src_filename = kzalloc((strlen(src_filename_start) + 1) * sizeof(char));
  strcpy(src_filename, src_filename_start);
  *src_filename_start = '\0';

  //get dentry for dest (which is nonexistent at this point)
  error = user_path_at(0, dest, 0, &destpt);
  if(error){
     printk("\n\n\nGot error for dest\n\n\n");
  }else{
     printk("\n\n\nNo error for dest\n\n\n");
  }

  return 0;
}
