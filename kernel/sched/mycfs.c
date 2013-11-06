#include <linux/sched.h>
#include <linux/slab.h>
#include "sched.h"

/*
   static void update_curr(struct mycfs_rq *mycfs_rq)
   {
   struct sched_mycfs_entity *curr = mycfs_rq->curr;

   unsigned long delta_exec;

   u64 now = mycfs_rq->rq->clock_task;

   delta_exec = (unsigned long)(now - curr->exec_start);

   if(!delta_exec)
   return;

   __update_curr(mycfs_rq, curr, delta_exec);
   curr->exec_start = now;



   }

   static inline void
   __update_curr(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *curr, unsigned long delta_exec)
   {
   unsigned long delta_exec_weighted;
   mycfs_rq->exec_clock += delta_exec; //not sure why fair.c needs a special function for this
   delta_exec_unweighted = 


   }
 */

static inline int entity_before(struct sched_mycfs_entity *a,
		struct sched_mycfs_entity *b)
{
	return (s64)(a->vruntime - b->vruntime) < 0;
}

static void __enqueue_mycfs_entity(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *mycfs_se)
{
	struct rb_node **link = &mycfs_rq->root.rb_node;
	struct rb_node *parent = NULL;
	struct sched_mycfs_entity *entry;
	int leftmost = 1;

	/*
	 * Find the right place in the rbtree:
	 */
	while (*link) {
		parent = *link;
		entry = rb_entry(parent, struct sched_mycfs_entity, run_node);
		/*
		 * We dont care about collisions. Nodes with
		 * the same key stay together.
		 */
		if (entity_before(mycfs_se, entry)) {
			link = &parent->rb_left;
		} else {
			link = &parent->rb_right;
			leftmost = 0;
		}
	}

	/*
	 * Maintain a cache of leftmost tree entries (it is frequently
	 * used):
	 */
	if (leftmost)
	mycfs_rq->rb_leftmost = &mycfs_se->run_node;

	rb_link_node(&mycfs_se->run_node, parent, link);
	rb_insert_color(&mycfs_se->run_node, &mycfs_rq->root);
}

	static void
enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;
	printk("\n\n\nEnqueuing\n\n\n");	
	if (mycfs) {
		mycfs_rq = &rq->my_cfs;
		__enqueue_mycfs_entity(mycfs_rq, mycfs);
	}
}

int alloc_mycfs_sched_group(struct task_group *tg, struct task_group *parent)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs_se;
	int i;


	tg->mycfs_rq = kzalloc(sizeof(mycfs_rq) * nr_cpu_ids, GFP_KERNEL);
	if (!tg->mycfs_rq)
		goto err;
	tg->mycfs_se = kzalloc(sizeof(mycfs_se) * nr_cpu_ids, GFP_KERNEL);
	if (!tg->mycfs_se)
		goto err;

	for (i = 0; i < nr_cpu_ids; i++) {
		mycfs_rq = kzalloc_node(sizeof(struct mycfs_rq),
				GFP_KERNEL, cpu_to_node(i));
		if (!mycfs_rq)
			goto err;

		mycfs_se = kzalloc_node(sizeof(struct sched_mycfs_entity),
				GFP_KERNEL, cpu_to_node(i));
		if (!mycfs_se)
			goto err_free_rq;

		mycfs_rq->root = RB_ROOT;
	}

	return 1;

err_free_rq:
	kfree(mycfs_rq);
err:
	return 0;
}

	static void
dequeue_entity(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *mycfs_se, int flags)
{

}

static struct task_struct *pick_next_task_mycfs(struct rq *rq){
	struct mycfs_rq *mycfs_rq = &rq->my_cfs; // Get the my_cfs run queue
	struct rb_node *left_most = mycfs_rq->rb_leftmost; // Get the left most child
	struct sched_mycfs_entity *entry = rb_entry(left_most, struct sched_mycfs_entity, run_node); // Get the entity of that child

	return container_of(entry, struct task_struct, mycfs); // Return the task struct of the task */
}

static void dequeue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;

	if(mycfs){
		mycfs_rq = &rq->my_cfs;
		dequeue_entity(mycfs_rq, mycfs, flags);
	}
}

	static void
entity_tick(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *curr, int queued)
{

}

static void task_tick_mycfs(struct rq *rq, struct task_struct *curr, int queued)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &curr->mycfs;

	if(mycfs){
		mycfs_rq = &rq->my_cfs;
		entity_tick(mycfs_rq, mycfs, queued);
	}
}

static void set_curr_task_mycfs(struct rq *rq)
{
	struct sched_mycfs_entity *mycfs = &rq->curr->mycfs;

	if(mycfs){
		struct mycfs_rq = &rq->my_cfs;


	}
}

static void yield_task_mycfs(struct rq *rq)
{
}

static void put_prev_task_mycfs(struct rq *rq, struct task_struct *prev)
{
}

	static void
check_preempt_curr_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
}

	static unsigned int
get_rr_interval_mycfs(struct rq *rq, struct task_struct *task)
{
	return 0;
}

#ifdef CONFIG_SMP
	static int
select_task_rq_mycfs(struct task_struct *p, int sd_flag, int flags)
{
	return 0; //task_cpu(p); /* stop tasks as never migrate */
}
#endif /* CONFIG_SMP */

	static void
task_fork (struct task_struct *p)
{
}

const struct sched_class mycfs_sched_class = {
	.next 			= &idle_sched_class,
	.enqueue_task   	= enqueue_task_mycfs,
	.dequeue_task   	= dequeue_task_mycfs,
	.pick_next_task 	= pick_next_task_mycfs,
	.task_tick   		= task_tick_mycfs,
	.set_curr_task 		= set_curr_task_mycfs,	
	.check_preempt_curr     = check_preempt_curr_mycfs,
	.yield_task 		= yield_task_mycfs,
	.get_rr_interval 	= get_rr_interval_mycfs,
	.put_prev_task		= put_prev_task_mycfs,
	.select_task_rq		= select_task_rq_mycfs,
	.task_fork		= task_fork,

};
