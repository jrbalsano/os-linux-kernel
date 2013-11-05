static void
enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	struct mycfs_rq *mycfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;
	
	if (mycfs && !mycfs->on_rq) {
		mycfs_rq = &rq->my_cfs
		enqueue_entity(mycfs_rq, mycfs, flags);
	}
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
