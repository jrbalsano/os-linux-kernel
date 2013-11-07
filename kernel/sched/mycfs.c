#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/smp.h>
#include "sched.h"

static void update_curr(struct mycfs_rq *mycfs_rq, struct rq *rq)
{

	/* //cannot implement this until set_curr_mycfs has been implemented so that ->curr is not null
	   struct sched_mycfs_entity *curr = mycfs_rq->curr;
	   u64 now = rq->clock_task;
	   unsigned long delta_exec;
	   printk("DGJ: CURRENT NOW VALUE: %llu\n",now);
	 */     

	/*
	 * Get the amount of time the current task was running
	 * since the last time we changed load (this cannot
	 * overflow on 32 bits):
	 */
	/*  
	    delta_exec = (unsigned long)(now - curr->exec_start);
	    if (!delta_exec)
	    return;

	    curr->vruntime += delta_exec;
	    curr->exec_start = now;  //do we actually need this here?
	 */	
}

static inline int entity_before(struct sched_mycfs_entity *a,
		struct sched_mycfs_entity *b)
{

	printk("DGJ[%d]: ENTITY BEFORE\n", smp_processor_id());
	return (s64)(a->vruntime - b->vruntime) < 0;
}

static void __enqueue_mycfs_entity(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *mycfs_se)
{

	struct rb_node **link = &mycfs_rq->root.rb_node;
	struct rb_node *parent = NULL;
	struct sched_mycfs_entity *entry;
	int leftmost = 1;
	int i = 1;
	printk("DGJ[%d]: __ENQUEUE_MYCFS_ENTITY\n", smp_processor_id());

	/*
	 * Find the right place in the rbtree:
	 */
	printk("DGJ[%d]: %p\n", smp_processor_id(), *link);
	while (*link) {
		printk("DGJ[%d]: INSIDE %d", smp_processor_id(), i++);
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

	printk("DGJ[%d]: ALMOST REACHING 1 ENDOF __ENQUEUE_MYCFS_ENTITY\n", smp_processor_id());

	rb_link_node(&mycfs_se->run_node, parent, link);

	printk("DGJ[%d]: ALMOST REACHING 2 ENDOF __ENQUEUE_MYCFS_ENTITY\n", smp_processor_id());

	rb_insert_color(&mycfs_se->run_node, &mycfs_rq->root);

	printk("DGJ[%d]: ALMOST REACHING 3 ENDOF __ENQUEUE_MYCFS_ENTITY\n", smp_processor_id());

}

	static void
enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{


	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;
	printk("DGJ[%d]: ENQUEUE_TASK_MYCFS\n", smp_processor_id());
	if (mycfs) {
		mycfs_rq = &rq->my_cfs;
		mycfs_rq->nr_running++;
		__enqueue_mycfs_entity(mycfs_rq, mycfs);
	}
}

int alloc_mycfs_sched_group(struct task_group *tg, struct task_group *parent)
{
	struct mycfs_rq *mycfs_rq;
	struct rq *one_cpu_rq;
	int i;
	struct rb_node **link;

	printk("DGJ[%d]: ALLOC_MYCFS_SCHED_GROUP\n", smp_processor_id());

	for (i = 0; i < nr_cpu_ids; i++) {
		one_cpu_rq = cpu_rq(i);
		mycfs_rq = &one_cpu_rq->my_cfs;
		mycfs_rq->root = RB_ROOT;
		mycfs_rq->nr_running = 0;
		mycfs_rq->rq = cpu_rq(i);

		/* TEST CODE DGJ */
		link = &mycfs_rq->root.rb_node;
		printk("DGJ[%d]: ALLOC %p\n", smp_processor_id(), *link);

	}

	return 1;
}

	static void
__dequeue_entity(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *mycfs_se, int flags)
{
	printk("DGJ[%d]: DEQUEUE_ENTITY\n", smp_processor_id());

	if(mycfs_rq->rb_leftmost == &mycfs_se->run_node){
		struct rb_node *next_node;

		next_node = rb_next(&mycfs_se->run_node);
		mycfs_rq->rb_leftmost = next_node;
	}

	rb_erase(&mycfs_se->run_node, &mycfs_rq->root);

}

static struct task_struct *pick_next_task_mycfs(struct rq *rq){
	struct mycfs_rq *mycfs_rq = &rq->my_cfs; // Get the my_cfs run queue
	struct rb_node *left_most = mycfs_rq->rb_leftmost; // Get the left most child
	struct sched_mycfs_entity *entry;
	struct task_struct *next_task;
	if (!left_most) {
		return NULL;
	}

	entry = rb_entry(left_most, struct sched_mycfs_entity, run_node); // Get the entity of that child
	entry->exec_start = rq->clock_task;

	next_task = container_of(entry, struct task_struct, mycfs); // Return the task struct of the task

	mycfs_rq->curr = next_task;

	return next_task 
}

static void dequeue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;
	printk("DGJ[%d]: DEQUEUE_TASK_MYCFS\n", smp_processor_id());

	if(mycfs){
		mycfs_rq = &rq->my_cfs;
		mycfs_rq->nr_running--;
		__dequeue_entity(mycfs_rq, mycfs, flags);
	}
}

	static void
entity_tick(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *curr, int queued, struct rq *rq)
{
	update_curr(mycfs_rq, rq);
	printk("DGJ[%d]:ENTITY_TICK\n", smp_processor_id());

}

static void task_tick_mycfs(struct rq *rq, struct task_struct *curr, int queued)
{


	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &curr->mycfs;
	printk("DGJ[%d]: TASK_TICK_MYCFS\n", smp_processor_id());

	if(mycfs){
		mycfs_rq = &rq->my_cfs;
		entity_tick(mycfs_rq, mycfs, queued, rq);
	}
}

static void set_curr_task_mycfs(struct rq *rq)
{
	//	struct sched_mycfs_entity *mycfs = &rq->curr->mycfs;
	printk("DGJ[%d]: SET_CURR_TASK_MYCFS\n", smp_processor_id());
	/*
	   if(mycfs){
	   struct mycfs_rq = &rq->my_cfs;
	   }
	 */
}

static void yield_task_mycfs(struct rq *rq)
{
	printk("DGJ[%d]: YIELD_TASK_MYCFS\n", smp_processor_id());
}

static void put_prev_task_mycfs(struct rq *rq, struct task_struct *prev)
{
	//      printk("DGJ[%d]: PUT_PREV_TASK_MYCFS\n", smp_processor_id());
}

	static void
check_preempt_curr_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	printk("DGJ[%d]: CHECK_PREEMPT_CURR_MYCFS\n", smp_processor_id());

}

	static unsigned int
get_rr_interval_mycfs(struct rq *rq, struct task_struct *task)
{
	printk("DGJ[%d]: GET_RR_INTERVAL_MYCFS\n", smp_processor_id());

	return 0;
}

#ifdef CONFIG_SMP
	static int
select_task_rq_mycfs(struct task_struct *p, int sd_flag, int flags)
{
	printk("DGJ[%d]: SELECT_TASK_RQ_MYCFS\n", smp_processor_id());

	return 0; //task_cpu(p); /* stop tasks as never migrate */
}
#endif /* CONFIG_SMP */

	static void
task_fork_mycfs (struct task_struct *p)
{
	printk("DGJ[%d]: TASK_FORK_MYCFS\n", smp_processor_id());

}

static void switched_to_mycfs(struct rq *rq, struct task_struct *p)
{
	printk("DGJ[%d]: SWITCHED_TO_MYCFS\n", smp_processor_id());
}

static void switched_from_mycfs(struct rq *rq, struct task_struct *p)
{ 
	printk("DGJ[%d]: SWITCHED_FROM_MYCFS\n", smp_processor_id());
}

	static void
prio_changed_mycfs(struct rq *rq, struct task_struct *p, int oldprio)
{
	printk("DGJ[%d]: PRIO_CHANGED_MYCFS\n", smp_processor_id());
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
	.task_fork		= task_fork_mycfs,

	.prio_changed		= prio_changed_mycfs,
	.switched_from		= switched_from_mycfs,
	.switched_to		= switched_to_mycfs,

};
