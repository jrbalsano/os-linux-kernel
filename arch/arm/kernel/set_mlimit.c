#include <linux/sched.h>


asmlinkage int set_mlimit(uid_t uid, long mem_max){

   struct user_struct *user = find_user(uid);
   struct user_struct *temp_user;
   if(user && mem_max > -1){
   	user->mem_max = mem_max;
	printk("SET MEM MAX of %d TO: %ld\n", uid, mem_max);
	temp_user = find_user(uid);
	printk("SET MEM MAX OF USER TO: %ld\n", temp_user->mem_max);
	return 0;
   }

   return -1;

}
