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
  char *safe_dest = getname(dest);
  char *safe_src = getname(src);
  /* char ext4_string[] = "ext4\0"; */
  char *dest_filename_start = strrchr(safe_dest, '/') + 1;
  char *dest_filename = kzalloc((strlen(dest_filename_start) + 1) * sizeof(char), 0);




  printk("safe_src: %s\n", safe_src);
  printk("safe_dest: %s\n", safe_dest);

  error = user_path_at(0, src, 0, &pt);
  if(!error){
    printk("\n\nChecking for errors\n\n");
    // Check if file is a directory or not
    if(!S_ISREG(pt.dentry->d_inode->i_mode)){
      printk("\n\nCHECKING IF IT'S DIRECTORY\n\n");
      return (-EPERM);
    }
    // Check if src is in a ext4 file system
    printk("FILE SYSTEM TYPE: %s\n", pt.dentry->d_sb->s_type->name);
    /* if(!strcmp(ext4_string, pt.dentry->d_sb->s_type->name)){ */
    /*   return (-EOPNOTSUPP); */
    /* } */
    printk("Passed all tests\n");
  }
  else{
    return -EEXIST;
  }

  //check for same filesystem by comparing mount
  
  // Separate filename from path
  strcpy(dest_filename, dest_filename_start);
  *dest_filename_start = '\0';

  //get dentry for dest (which is nonexistent at this point)
  error = user_path_at(0, dest, 0, &destpt);
  if(error){
     printk("\n\n\nGot error for dest\n\n\n");
  }else{
     printk("\n\n\nNo error for dest\n\n\n");
  }

  return 0;
}
