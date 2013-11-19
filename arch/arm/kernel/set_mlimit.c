#include <linux/sched.h>


asmlinkage int set_mlimit(uid_t uid, long mem_max){

   user_struct *user = find_user(uid);
   
   if(user && mem_max > -1){
   	user->mem_max = mem_max;
	return 0;
   }

   return -1;

}
