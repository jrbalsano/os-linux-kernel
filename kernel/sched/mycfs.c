
static void
enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags)
{
	struct mycfs_rq *cfs_rq;
	struct sched_mycfs_entity *mycfs = &p->mycfs;
}
