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
  
  struct path pt;
  printk("\n\n BEFORE KERN PATH\n\n");
  if(kern_path(src, LOOKUP_FOLLOW | LOOKUP_DIRECTORY,  &pt) == 0){
    printk("\n\n AFTER KERN PATH\n\n");
    // Check if file is a directory or not
    if(!S_ISREG(pt.dentry->d_inode->i_mode)){
      printk("\n\nCHECKING IF IT DIRECTORY\n\n");
      return (-EPERM);
    }
  }
  return 0;
}
