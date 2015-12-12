#include <stdlib.h>
#include <stdio.h>

#include <gmodule.h>

#include "Qvm.h"

#include "_types.h"

static q_vm_t *vm = NULL;

/* >>> initialize context <<< */

void q_ctx_init(q_context_t *ctx, size_t ops_max, size_t stack_max) {
	if (!vm) {
		vm = malloc(sizeof(q_vm_t));
		vm->ops = calloc(ops_max, sizeof(q_operation_t *));
		vm->ops_len = 0; vm->ops_max = ops_max;
		vm->lhash = g_hash_table_new(g_str_hash, g_str_equal);
		vm->mhash = g_hash_table_new(g_str_hash, g_str_equal);
		vm->vhash = g_hash_table_new(g_str_hash, g_str_equal);
	}
	ctx->vm = (void *)vm;
	ctx->stack = calloc(stack_max, sizeof(q_value_t *));
	ctx->stack_max = stack_max;
	ctx->trace = (size_t)0;
	ctx->err_handler = NULL;
}

// TODO free(ops), free(stack), g_hash_table_destroy

/* >>> stack <<< */

void q_push(q_context_t *ctx, q_value_t *val) {
	size_t sp = ctx->sp;
	
	if (sp < ctx->stack_max) {
		ctx->stack[sp] = val;
		++(ctx->sp);
	} else {
		// TODO increase stack[]
		;
	}
}

q_value_t *q_pop(q_context_t *ctx) {
	size_t sp;
	
	if (ctx->sp > 0) {
		sp = --(ctx->sp);
		q_value_t *val = ctx->stack[sp];
		ctx->stack[sp] = NULL;
		return val;
	} else {
		return NULL;
	}
}

q_value_t *q_peek(q_context_t *ctx, _s8_t idx) {
	size_t sp;
	
	if (idx <= 0 && (sp = (ctx->sp + idx - 1)) >= 0) {
		q_value_t *val = ctx->stack[sp];
		return val;
	} else {
		return NULL;
	}
}

/* >>> vars <<< */

q_value_t *q_get(q_context_t *ctx, _string_t name) {
	return (q_value_t *)g_hash_table_lookup(vm->vhash, name);
}

void q_set(q_context_t *ctx, _string_t name, q_value_t *val) {
	if (val) {
		g_hash_table_insert(vm->vhash, name, (void *)val);
	} else {
		g_hash_table_remove(vm->vhash, name);
	}
}

/* >>> ops <<< */

void q_ops_push(q_context_t *ctx, q_operation_t *op) {
	size_t idx = (vm->ops_len)++;
	if (idx < vm->ops_max)
		vm->ops[idx] = op;
	else
		// TODO increase ops[]
		;
}

void q_ops_label(q_context_t *ctx, _string_t label) {
	size_t idx = vm->ops_len;
	
	if (idx < vm->ops_max) {
		g_hash_table_insert(vm->lhash, label, (void *)idx);
		// printf("%zu ----> %zu (%s)\n", idx, (size_t)g_hash_table_lookup(ctx->lhash, label), label);
	}
}

int q_ops_exec(q_context_t *ctx) {
	q_operation_t *op;
	size_t pc = ctx->pc;

	if (pc >= 0 && pc < vm->ops_len) {
		op = vm->ops[pc];
		++(ctx->pc);
		return op->exec(op, ctx);
	} else {
		return -1; // TODO ERROR_CODE FOR NO OPS
	}
}

/* >>> exec <<< */

static q_value_t *q_s32(_s32_t data) {
	q_s32_t *val = (q_s32_t *)q_gc_malloc(sizeof(q_s32_t));
	val->value.type = S32;
	val->_data = data;
	return (q_value_t *)val;
}

void q_exec(q_context_t *ctx, _string_t label) {
	int iret, exitcode = 0;
	q_err_handler_t *h;
	
	if (vm->ops_len == 0)
		return; 
	
	if (label)
		// TODO check label existance
		ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, label);
	else
		ctx->pc = 0;
	
	ctx->sp = 0;	
	
	for(;;) {
		if ((iret = q_ops_exec(ctx)) != OP_OK) {
			if (iret == OP_EXIT) {
				q_value_t *val = q_pop(ctx);
				if (val && val->type == S32) {
					exitcode = ((q_s32_t *)val)->_data;
				}
				exit(exitcode);
			} else if (ctx->err_handler) {
				h = ctx->err_handler;
				ctx->err_handler = h->next;
				
				q_push(ctx, q_s32(iret)); // push error code
				
				// TODO check label existance
				ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, h->label);
			} else {
				fprintf(stderr, "*** %s:%d error: %d\n", __func__, __LINE__, iret);
				q_stack_trace(ctx);
				//q_dump(ctx);
				
				/* stop execution */
				break;
			}
		}
	}
}

/** >>> dlopen <<< */

void q_dlopen(q_context_t *ctx, _string_t mod) {
	char *lib;
	GModule *module;
	
	if (!g_module_supported()) {
		fprintf(stderr, "*** no modules support ... \n"); // TODO
		exit(-1);
	}
	
	lib = getenv(mod);
	if (!lib) lib = mod;
	
	module = g_module_open(lib, G_MODULE_BIND_LAZY);
	if (!module) {
		fprintf(stderr, "*** dlopen: %s\n", g_module_error ());
		exit(1);
	}
	
	g_hash_table_insert(vm->mhash, mod, (void *)module);
}

/* >>> stack trace <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_call_t;

void q_stack_trace(q_context_t *ctx) {
	q_trace_t *t = ctx->trace;
	q_call_t *cop = !t ? NULL : (q_call_t *)ctx->vm->ops[t->pc - 1];
	
	if (cop) {
		fprintf(stderr, ">>> stack trace: %s(%p), pc=%p\n"
			, cop->_label
			, (void *)g_hash_table_lookup(ctx->vm->lhash, cop->_label)
			, (void *)(ctx->pc-1));
	
		while (t) {
			char *label = ((q_call_t *)ctx->vm->ops[t->pc - 1])->_label;
			fprintf(stderr, "%10p: call %s(%p)\n"
				, (void *)t->pc
				, label
				, (void *)g_hash_table_lookup(ctx->vm->lhash, label));
			t = t->next;
		}
	}
}

/* >>> dump <<< */

void q_dump(q_context_t *ctx) {
	size_t sp = ctx->sp;


	printf(">>> sp=%p (%p) pc=%p (%p:%p)\n"
		, (void *)sp
		, (void *)ctx->stack_max
		, (void *)ctx->pc
		, (void *)vm->ops_len
		, (void *)vm->ops_max);
	
	while (sp > 0) {
		q_value_t *val = ctx->stack[--sp];
		switch(val->type) {

		case S8:
			printf("[%8x] S8     : %d\n", (int)sp, ((q_s8_t  *)val)->_data);
			break;
		case S16:
			printf("[%8x] S16    : %d\n", (int)sp, ((q_s16_t *)val)->_data);
			break;
		case S32:
			printf("[%8x] S32    : %ld\n", (int)sp, ((q_s32_t *)val)->_data);
			break;
		case S64:
			printf("[%8x] S64    : %lld\n", (int)sp, ((q_s64_t *)val)->_data);
			break;
			
		case U8:
			printf("[%8x] U8     : %u\n", (int)sp, ((q_u8_t  *)val)->_data);
			break;
		case U16:
			printf("[%8x] U16    : %u\n", (int)sp, ((q_u16_t *)val)->_data);
			break;
		case U32:
			printf("[%8x] U32    : %lu\n", (int)sp, ((q_u32_t *)val)->_data);
			break;
		case U64:
			printf("[%8x] U64    : %llu\n", (int)sp, ((q_u64_t *)val)->_data);
			break;
			
		case FLOAT:
			printf("[%8x] FLOAT  : %g\n", (int)sp, ((q_float_t *)val)->_data);
			break;
		case DOUBLE:
			printf("[%8x] DOUBLE : %g\n", (int)sp, ((q_double_t *)val)->_data);
			break;

		case STRING:
			printf("[%8x] STRING : %s\n", (int)sp, ((q_string_t *)val)->_data);
			break;
		case PTR:
			printf("[%8x] PTR    : %p\n", (int)sp, ((q_ptr_t *)val)->_data);
			break;
		
		case THREAD:
			printf("[%8x] THREAD : %p\n", (int)sp, ((q_thread_t *)val)->_data);
			break;	
		
		default:
			fprintf(stderr, "???\n");
		}
	}
	
	//if (ctx->sp > 0) puts("\n");
}

