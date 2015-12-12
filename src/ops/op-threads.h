/* >>> q_run_t <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
	q_context_t *_ctx;
} q_run_t;

static void *_thread_run(void *arg) {printf("------------------xxx\n");
	q_run_t *val = (q_run_t *)arg;
	q_context_t *ctx = (q_context_t *)q_gc_malloc(sizeof(q_context_t));
	
	q_ctx_init(ctx, 255, 255);
	val->_ctx = ctx;
	q_exec(ctx, val->_label);
}

static int op_run(q_operation_t *self, q_context_t *ctx) {printf("------------------op_run\n");
	q_run_t *op = (q_run_t *)self;
	pthread_t *t = (pthread_t *)q_gc_malloc(sizeof(pthread_t));
	int iret;
	
	iret = pthread_create(t, NULL, _thread_run, (void *)op);
	if (iret) {
		fprintf(stderr, "*** %s:%d return code: %d\n", __func__, __LINE__, iret);
		return -1;
	}

	q_push(ctx, (q_value_t *)q_thread((_ptr_t)t));
	
	return 0;
}

q_operation_t *q_op_run(_string_t label) {
	q_run_t *op = (q_run_t *)q_gc_malloc(sizeof(q_run_t));
	op->op.exec = op_run;
	op->_label = label;
	return (q_operation_t *)op;
}
