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
#include <linux/unistd.h>



asmlinkage int sys_ext4_cowcopy(const char __user *src, const char __user *dest) {

  /* struct file * myFile = filp_open(src, O_RDONLY, 0644); */
  
  struct path pt; //path for src
  struct path destpt; //path for dest
  struct dentry *temp_dentry;
  int error;
  char *safe_dest = getname(dest);
  char *safe_src = getname(src);
  char ext4_string[] = "ext4";
  /* mm_segment_t fs; */

  /* int i = 1; */
  /* int j; */



  printk("safe_src: %s\n", safe_src);
  printk("safe_dest: %s\n", safe_dest);

  error = user_path_at(AT_FDCWD, src, 0, &pt);
  if(!error){
    printk("\n\nChecking for errors\n\n");
    
    // Check if file is a directory or not
    if(!S_ISREG(pt.dentry->d_inode->i_mode)){
      printk("\n\nCHECKING IF IT'S DIRECTORY\n\n");
      return (-EPERM);
    }
    
    // Check if src is in a ext4 file system
    printk("FILE SYSTEM TYPE: %s\n", pt.dentry->d_sb->s_type->name);
    if(strcmp(ext4_string, pt.dentry->d_sb->s_type->name)){
      return (-EOPNOTSUPP);
    }
    
    temp_dentry = user_path_create(AT_FDCWD, dest, &destpt, 0);
    // Check if file already exists
    if(temp_dentry == ERR_PTR(-EEXIST)){
      return (-EEXIST);
    }
    // Check if src and dest are in the same device
    if(pt.mnt->mnt_root == destpt.mnt->mnt_root){
      return (-EXDEV);
    }

    // Check if file is being written to
    printk("\n\nCHECKING IF BEING WRITTEN TO\n\n");
    if (pt.dentry->d_inode->i_writecount.counter > 0) {
      return -EPERM;
    }
    
    printk("Passed all tests\n");
  }
  else {
    printk("error: %d", error);
    return error;
  }

  
  //AT_FDXWD, user_path_create, link, open are inside namei.c
  
  /* error = sys_link(src, dest); */
  /* if (error) { */
  /*   printk("error: %d\n", error); */
  /*   return error; */
  /* } */

  /* fs = get_fs();     /\* save previous value *\/ */
  /* set_fs (get_ds()); /\* use kernel limit *\/ */

  /* system calls can be invoked */

  /* error = sys_setxattr(safe_dest, "system.cow_moo", &i, sizeof(int), 0); */
  /* if(error){ */
  /*   printk("Error from setxattr: %d\n", error); */
  /*   return error; */
  /* } */
  /* error = sys_getxattr(safe_dest, "system.cow_moo", &j, sizeof(int)); */
  /* if(error<0){ */
  /*   printk("Error from getxattr: %d\n", error); */
  /*   return error; */
  /* } */
  /* set_fs(fs); /\* restore before returning to user space *\/ */

  /* printk("i: %d, j: %d\n", i, j); */

  /* if(i == j){ */
  /*   printk("SUCCESS\n"); */
  /* } */

  return 0;
}
