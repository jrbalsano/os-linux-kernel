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


