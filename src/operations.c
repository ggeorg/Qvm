#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include <ctype.h>

#include <ffi.h>
#include <glib.h>
#include <gmodule.h>

#include <pthread.h>

#include "Qvm.h"
#include "qvm-gc.h"

#include "operations.h"

/* >>> q types <<< */

static q_s8_t *q_s8(_s8_t data) {
	q_s8_t *val = (q_s8_t *)q_gc_malloc(sizeof(q_s8_t));
	val->value.type = S8;
	val->_data = data;
	return val;
}

static q_s16_t *q_s16(_s16_t data) {
	q_s16_t *val = (q_s16_t *)q_gc_malloc(sizeof(q_s16_t));
	val->value.type = S16;
	val->_data = data;
	return val;
}

static q_s32_t *q_s32(_s32_t data) {
	q_s32_t *val = (q_s32_t *)q_gc_malloc(sizeof(q_s32_t));
	val->value.type = S32;
	val->_data = data;
	return val;
}

static q_s64_t *q_s64(_s64_t data) {
	q_s64_t *val = (q_s64_t *)q_gc_malloc(sizeof(q_s64_t));
	val->value.type = S64;
	val->_data = data;
	return val;
}

static q_u8_t *q_u8(_u8_t data) {
	q_u8_t *val = (q_u8_t *)q_gc_malloc(sizeof(q_u8_t));
	val->value.type = U8;
	val->_data = data;
	return val;
}

static q_u16_t *q_u16(_u16_t data) {
	q_u16_t *val = (q_u16_t *)q_gc_malloc(sizeof(q_u16_t));
	val->value.type = U16;
	val->_data = data;
	return val;
}

static q_u32_t *q_u32(_u32_t data) {
	q_u32_t *val = (q_u32_t *)q_gc_malloc(sizeof(q_u32_t));
	val->value.type = U32;
	val->_data = data;
	return val;
}

static q_u64_t *q_u64(_u64_t data) {
	q_u64_t *val = (q_u64_t *)q_gc_malloc(sizeof(q_u64_t));
	val->value.type = U64;
	val->_data = data;
	return val;
}

static q_float_t *q_float(_float_t data) {
	q_float_t *val = (q_float_t *)q_gc_malloc(sizeof(q_float_t));
	val->value.type = FLOAT;
	val->_data = data;
	return val;
}

static q_double_t *q_double(_double_t data) {
	q_double_t *val = (q_double_t *)q_gc_malloc(sizeof(q_double_t));
	val->value.type = DOUBLE;
	val->_data = data;
	return val;
}

static q_string_t *q_string(_string_t data) {
	q_string_t *val = (q_string_t *)q_gc_malloc(sizeof(q_string_t));
	val->value.type = STRING;
	val->_data = data;
	return val;
}

static q_ptr_t *q_ptr(_ptr_t data) {
	q_ptr_t *val = (q_ptr_t *)q_gc_malloc(sizeof(q_ptr_t));
	val->value.type = PTR;
	val->_data = data;
	return val;
}

static q_thread_t *q_thread(_ptr_t data) {
	q_thread_t *val = (q_thread_t *)q_gc_malloc(sizeof(q_thread_t));
	val->value.type = THREAD;
	val->_data = data;
	return val;
}

/* >>> q_push_s8_t <<< */

typedef struct {
	q_operation_t op;
	_s8_t _val;
} q_push_s8_t;

static int op_push_s8(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s8(((q_push_s8_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_s8(_s8_t val) {
	q_push_s8_t *op = (q_push_s8_t *)q_gc_malloc(sizeof(q_push_s8_t));
	op->op.exec = op_push_s8;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_s16_t <<< */

typedef struct {
	q_operation_t op;
	_s16_t _val;
} q_push_s16_t;

static int op_push_s16(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s16(((q_push_s16_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_s16(_s16_t val) {
	q_push_s16_t *op = (q_push_s16_t *)q_gc_malloc(sizeof(q_push_s16_t));
	op->op.exec = op_push_s16;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_s32_t <<< */

typedef struct {
	q_operation_t op;
	_s32_t _val;
} q_push_s32_t;

static int op_push_s32(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s32(((q_push_s32_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_s32(_s32_t val) {
	q_push_s32_t *op = (q_push_s32_t *)q_gc_malloc(sizeof(q_push_s32_t));
	op->op.exec = op_push_s32;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_s64_t <<< */

typedef struct {
	q_operation_t op;
	_s64_t _val;
} q_push_s64_t;

static int op_push_s64(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s64(((q_push_s64_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_s64(_s64_t val) {
	q_push_s64_t *op = (q_push_s64_t *)q_gc_malloc(sizeof(q_push_s64_t));
	op->op.exec = op_push_s64;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_u8_t <<< */

typedef struct {
	q_operation_t op;
	_u8_t _val;
} q_push_u8_t;

static int op_push_u8(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u8(((q_push_u8_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_u8(_u8_t val) {
	q_push_u8_t *op = (q_push_u8_t *)q_gc_malloc(sizeof(q_push_u8_t));
	op->op.exec = op_push_u8;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_u16_t <<< */

typedef struct {
	q_operation_t op;
	_u16_t _val;
} q_push_u16_t;

static int op_push_u16(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u16(((q_push_u16_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_u16(_u16_t val) {
	q_push_u16_t *op = (q_push_u16_t *)q_gc_malloc(sizeof(q_push_u16_t));
	op->op.exec = op_push_u16;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_u32_t <<< */

typedef struct {
	q_operation_t op;
	_u32_t _val;
} q_push_u32_t;

static int op_push_u32(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u32(((q_push_u32_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_u32(_u32_t val) {
	q_push_u32_t *op = (q_push_u32_t *)q_gc_malloc(sizeof(q_push_u32_t));
	op->op.exec = op_push_u32;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_u64_t <<< */

typedef struct {
	q_operation_t op;
	_u64_t _val;
} q_push_u64_t;

static int op_push_u64(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u64(((q_push_u64_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_u64(_u64_t val) {
	q_push_u64_t *op = (q_push_u64_t *)q_gc_malloc(sizeof(q_push_u64_t));
	op->op.exec = op_push_u64;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_float_t <<< */

typedef struct {
	q_operation_t op;
	_float_t _val;
} q_push_float_t;

static int op_push_float(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_float(((q_push_float_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_float(_float_t val) {
	q_push_float_t *op = (q_push_float_t *)q_gc_malloc(sizeof(q_push_float_t));
	op->op.exec = op_push_float;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_double_t <<< */

typedef struct {
	q_operation_t op;
	_double_t _val;
} q_push_double_t;

static int op_push_double(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_double(((q_push_double_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_double(_double_t val) {
	q_push_double_t *op = (q_push_double_t *)q_gc_malloc(sizeof(q_push_double_t));
	op->op.exec = op_push_double;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_string_t <<< */

typedef struct {
	q_operation_t op;
	_string_t _val;
} q_push_string_t;

static int op_push_string(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_string(((q_push_string_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_string(_string_t val) {
	q_push_string_t *op = (q_push_string_t *)q_gc_malloc(sizeof(q_push_string_t));
	op->op.exec = op_push_string;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_ptr_t <<< */

typedef struct {
	q_operation_t op;
	_ptr_t _val;
} q_push_ptr_t;

static int op_push_ptr(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_ptr(((q_push_ptr_t *)self)->_val));
	return 0;
}

q_operation_t *q_op_push_ptr(_ptr_t val) {
	q_push_ptr_t *op = (q_push_ptr_t *)q_gc_malloc(sizeof(q_push_ptr_t));
	op->op.exec = op_push_ptr;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_push_t <<< */

typedef struct {
	q_operation_t op;
	_string_t _var;
} q_push_t;

static int op_push(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val = q_get(ctx, ((q_push_t *)self)->_var);
	if (val) {
		q_push(ctx, val);
		return OP_OK;
	} else {
		return ERROR_VALUE_IS_NULL;
	}
}

q_operation_t *q_op_push(_string_t var) {
	q_push_t *op = (q_push_t *)q_gc_malloc(sizeof(q_push_t));
	op->op.exec = op_push;
	op->_var = var;
	return (q_operation_t *)op;
}

/* >>> q_pop_t <<< */

typedef struct {
	q_operation_t op;
	_s8_t _val;
} q_pop_t;

static int op_pop(q_operation_t *self, q_context_t *ctx) {
	int i = ((q_pop_t *)self)->_val;
	while(i-- > 0) q_pop(ctx); // TODO optimize
	return 0;
}

static q_pop_t *_op_pop = NULL;
q_operation_t *q_op_pop(void) {
	if (_op_pop == NULL) { // TODO synchronization
		_op_pop = (q_pop_t *)q_gc_malloc(sizeof(q_pop_t));
		_op_pop->op.exec = op_pop;
		_op_pop->_val = 1;
	}
	return (q_operation_t *)_op_pop;
}

q_operation_t *q_op_pop_n(_s8_t val) {
	q_pop_t *op = (q_pop_t *)q_gc_malloc(sizeof(q_pop_t));
	op->op.exec = op_pop;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> q_pop_v_t <<< */

typedef struct {
	q_operation_t op;
	_string_t _var;
} q_pop_v_t;

static int op_pop_v(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val = q_pop(ctx);
	if (val) {
		q_set(ctx, ((q_pop_v_t *)self)->_var, val);
		return OP_OK;
	} else {
		return ERROR_VALUE_IS_NULL;
	}
}

q_operation_t *q_op_pop_v(_string_t var) {
	q_pop_v_t *op = (q_pop_v_t *)q_gc_malloc(sizeof(q_pop_v_t));
	op->op.exec = op_pop_v;
	op->_var = var;
	return (q_operation_t *)op;
}

/* >>> q_rot_t <<< */

typedef struct {
	q_operation_t op;
	_s8_t _val;
} q_rot_t;

static int op_rot(q_operation_t *self, q_context_t *ctx) {
	q_rot_t *op = (q_rot_t *)self;
	gboolean clockwise = op->_val > 0;
	int steps = abs(op->_val);
	if (ctx->sp > steps) {
		size_t idx1 = ctx->sp - 1;
		size_t idx2 = idx1 - steps;
		if (clockwise) {
			q_value_t *val = ctx->stack[idx2];
			for (int i = idx2; i < idx1; i++) {
				ctx->stack[i] = ctx->stack[i+1];
			}
			ctx->stack[idx1] = val;
		} else {
			q_value_t *val = ctx->stack[idx1];
			for (int i = idx1; i > idx2; i--) {
				ctx->stack[i] = ctx->stack[i-1];
			}
			ctx->stack[idx2] = val;
		}
		return 0;
	} else {
		fprintf(stderr, "*** q_op_rot error: %p, %d\n", (void *)ctx->sp, op->_val);
		return -1;
	}
	return 0;
}

q_operation_t *q_op_rot() {
	return q_op_rot_n(1); // TODO optimize
}

q_operation_t *q_op_rot_n(_s8_t val) {
	q_rot_t *op = (q_rot_t *)q_gc_malloc(sizeof(q_rot_t));
	op->op.exec = op_rot;
	op->_val = val;
	return (q_operation_t *)op;
}

/* >>> Convertion Operations <<< */

#include "ops/op-conversion.h"

/* >>> Arithmetic Operations <<< */

#include "ops/op-arithmetic.h"

/* >>> Branching and Conditionals Operations <<< */

#include "ops/op-branching.h"

/* >>> Subroutines <<< */

#include "ops/op-subroutines.h"

/* >>> Threads <<< */

#include "ops/op-threads.h"

/* >>> q_dump_t <<< */

typedef struct {
	q_operation_t op;
} q_dump_t;

static int op_dump(q_operation_t *self, q_context_t *ctx) {
	q_dump_t *op = (q_dump_t *)self;
	q_dump(ctx); /* calling Qvm::q_dump() */
	return 0;
}

static q_dump_t *_op_dump = NULL;
q_operation_t *q_op_dump(void) {
	if (_op_dump == NULL) { // TODO synchronization
		_op_dump = (q_dump_t *)q_gc_malloc(sizeof(q_dump_t));
		_op_dump->op.exec = op_dump;
	}
	return (q_operation_t *)_op_dump;
}

/* >>> q_print_t <<< */

typedef struct {
	q_operation_t op;
} q_print_t;

static int op_print(q_operation_t *self, q_context_t *ctx) {
	q_print_t *op = (q_print_t *)self;
	q_value_print(q_pop(ctx));
	return 0;
}

static q_print_t *_op_print = NULL;
q_operation_t *q_op_print(void) {
	if (_op_print == NULL) { // TODO synchronization
		_op_print = (q_print_t *)q_gc_malloc(sizeof(q_print_t));
		_op_print->op.exec = op_print;
	}
	return (q_operation_t *)_op_print;
}

