#include <linux/sched.h>
#include "sched.h"

static void
enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;
	
	if (mycfs) {
		cfs_rq = &rq->my_cfs
		__enqueue_entity(mycfs_rq, mycfs, flags);
	}
}

static inline int entity_before(struct sched_entity *a,
				struct sched_entity *b)
{
	return (s64)(a->vruntime - b->vruntime) < 0;
}

static void __enqueue_entity(struct mycfs_rq *mycfs_rq, struct sched_mycfs_entity *mycfs_se)
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

static void dequeue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;

	if(mycfs && mycfs->on_rq){
		mycfs_rq = &rq->my_cfs;
		dequeue_entity(mycfs_rq, mycfs, flags);
	}
}


static void
dequeue_entity(struct mycfs_rq *mycfs_rq, struct mycfs_sched_entity, int flags)
{
//	update_curr(cfs_rq);
	
}



const struct sched_class mycfs_sched_class = {
	.next 			= &idle_sched_class,
	.enqueue_task   	= enqueue_task_mycfs,
	.dequeue_task   	= dequeue_task_mycfs,
	.pick_next_task 	= pick_next_task_mycfs,
	.set_curr_task		= set_curr_task_mycfs,
	.task_tick   		= task_tick_mycfs,

}
