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

		cfs_rq->root = RB_ROOT;
	}

	return 1;

err_free_rq:
	kfree(cfs_rq);
err:
	return 0;
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
