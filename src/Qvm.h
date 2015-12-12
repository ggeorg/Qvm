#ifndef QVM_QVM_H
#define QVM_QVM_H

#include <glib.h>

typedef signed char        _s8_t;
typedef signed short       _s16_t;
typedef signed long int    _s32_t;
typedef signed long long   _s64_t;

typedef unsigned char      _u8_t;
typedef unsigned short     _u16_t;
typedef unsigned long int  _u32_t;
typedef unsigned long long _u64_t;

typedef float              _float_t;
typedef double             _double_t;

typedef char *	            _string_t;
typedef void *             _ptr_t;

typedef signed long int		_s32arr_t;

typedef struct q_vm           q_vm_t;
typedef struct q_trace        q_trace_t;		
typedef struct q_err_handler  q_err_handler_t;
typedef struct q_context      q_context_t;
typedef struct q_operation    q_operation_t;
typedef struct q_value        q_value_t;

struct q_vm {
	q_operation_t **ops;
	size_t ops_len, ops_max;
	
	GHashTable *lhash;	/* labels hash */
	GHashTable *mhash;	/* modules hash */
	GHashTable *vhash;	/* vars hash */
};

struct q_trace {
	q_trace_t *next;
	size_t pc;
};

struct q_err_handler {
	q_err_handler_t *next;
	_string_t label;
};

struct q_context {
	size_t pc, sp;
	q_value_t **stack;
	size_t stack_max;
	q_vm_t *vm;
	
	/* trace stack */
	q_trace_t *trace;
	
	/* error handler stack */
	q_err_handler_t *err_handler;
};

struct q_operation {
	 int (*exec)(q_operation_t *self, q_context_t *context);
};

#define S8       1
#define U8       2
#define S16      3 
#define U16      4 
#define S32      5 
#define U32      6
#define S64      7 
#define U64      8
#define FLOAT    9 
#define DOUBLE   10
#define STRING   11
#define PTR      12

#define S8A      21
#define U8A      22
#define S16A     23 
#define U16A     24 
#define S32A     25 
#define U32A     26
#define S64A     27 
#define U64A     28
#define FLOATA   29 
#define DOUBLEA  30

#define THREAD   100

struct q_value {
	_u8_t type;
};

#define OP_OK        0
#define OP_EXIT	   1
#define OP_FAILED   -1

#define ERROR_VALUE_IS_NULL      -1000
#define ERROR_ILLIGAL_ARGUMENT   -1001
#define ERROR_DIVISION_BY_ZERO   -1003
#define ERROR_UNBALANCED_CLR_OP  -1004

void q_ctx_init(q_context_t *ctx, size_t ops_max, size_t stack_max);

void q_push(q_context_t *ctx, q_value_t *val);
q_value_t *q_pop(q_context_t *ctx);
q_value_t *q_peek(q_context_t *ctx, _s8_t idx);

q_value_t *q_get(q_context_t *ctx, _string_t name);
void q_set(q_context_t *ctx, _string_t name, q_value_t *val);

void q_ops_push(q_context_t *ctx, q_operation_t *op);
void q_ops_label(q_context_t *ctx, _string_t label);
int  q_ops_exec(q_context_t *ctx);

void q_exec(q_context_t *ctx, _string_t label);

void q_stack_trace(q_context_t *ctx);
void q_dump(q_context_t *ctx);

void q_dlopen(q_context_t *ctx, _string_t mod);

#endif
