/* To be included by operations.c */

static int q_value_cmp(q_value_t *val1, q_value_t *val2) {
	int type = (val1->type >= val2->type) ? val1->type : val2->type;

	switch(type) {
	case S8: {
			_s8_t v1 = (val1->type == type) 
				? ((q_s8_t *)val1)->_data : to_s8(val1);
			_s8_t v2 = (val2->type == type) 
				? ((q_s8_t *)val2)->_data : to_s8(val2);
		
			return (v2 - v1);
		}
		break;
	case S16: {
			_s16_t v1 = (val1->type == type) 
				? ((q_s16_t *)val1)->_data : to_s16(val1);
			_s16_t v2 = (val2->type == type) 
				? ((q_s16_t *)val2)->_data : to_s16(val2);
					
			return (v2 - v1);
		}
		break;
	case S32: {
			_s32_t v1 = (val1->type == type) 
				? ((q_s32_t *)val1)->_data : to_s32(val1);
			_s32_t v2 = (val2->type == type) 
				? ((q_s32_t *)val2)->_data : to_s32(val2);
				
			return (v2 - v1);
		}
		break;
	case S64: {
			_s64_t v1 = (val1->type == type) 
				? ((q_s64_t *)val1)->_data : to_s64(val1);
			_s64_t v2 = (val2->type == type) 
				? ((q_s64_t *)val2)->_data : to_s64(val2);
				
			return (v2 - v1);
		}
		break;
	case U8: {
			_u8_t v1 = (val1->type == type) 
				? ((q_u8_t *)val1)->_data : to_u8(val1);
			_u8_t v2 = (val2->type == type) 
				? ((q_u8_t *)val2)->_data : to_u8(val2);
				
			return (v2 - v1);
		}
		break;
	case U16: {
			_u16_t v1 = (val1->type == type) 
				? ((q_u16_t *)val1)->_data : to_u16(val1);
			_u16_t v2 = (val2->type == type) 
				? ((q_u16_t *)val2)->_data : to_u16(val2);
				
			return (v2 - v1);
		}
		break;
	case U32: {
			_u32_t v1 = (val1->type == type) 
				? ((q_u32_t *)val1)->_data : to_u32(val1);
			_u32_t v2 = (val2->type == type) 
				? ((q_u32_t *)val2)->_data : to_u32(val2);
				
			return (v2 - v1);
		}
		break;
	case U64: {
			_u64_t v1 = (val1->type == type) 
				? ((q_u64_t *)val1)->_data : to_u64(val1);
			_u64_t v2 = (val2->type == type) 
				? ((q_u64_t *)val2)->_data : to_u64(val2);
				
			return (v2 - v1);
		}
		break;
	case FLOAT: {
			_float_t v1 = (val1->type == type) 
				? ((q_float_t *)val1)->_data : to_float(val1);
			_float_t v2 = (val2->type == type) 
				? ((q_float_t *)val2)->_data : to_float(val2);
				
			_float_t v3 = (v2 - v1);
			
			return (v3 == 0.0) ? 0 : ((v3 > 0) ? 1 : -1);
		}
		break;
	case DOUBLE: {
			_double_t v1 = (val1->type == type) 
				? ((q_double_t *)val1)->_data : to_double(val1);
			_double_t v2 = (val2->type == type) 
				? ((q_double_t *)val2)->_data : to_double(val2);
				
			_double_t v3 = (v2 - v1);
			
			return (v3 == 0.0) ? 0 : ((v3 > 0) ? 1 : -1);
		}
		break;
	default:
		// TODO report error
		fprintf(stderr, "!!! %s: illegal argument(s)\n", __func__);
		exit(1);
	}
}

/* >>> jmp <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jmp_t;

static int op_jmp(q_operation_t *self, q_context_t *ctx) {
	q_jmp_t *op = (q_jmp_t *)self;
	// TODO check label exists
	ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);
	return 0;
}

q_operation_t *q_op_jmp(_string_t label) {
	q_jmp_t *op = (q_jmp_t *)q_gc_malloc(sizeof(q_jmp_t));
	op->op.exec = op_jmp;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jeq (jmp equal) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jeq_t;

static int op_jeq(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val1, *val2;
	q_jeq_t *op = (q_jeq_t *)self;
	
	if (!(val1 = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(val2 = q_peek(ctx, -1))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(is_numeric(val1) && is_numeric(val2))) {
		fprintf(stderr, "*** %s:%d illegal argument(s)\n", __func__, __LINE__);
		exit(-1);
	}
	
	if (q_value_cmp(val1, val2) == 0) {
		// TODO check label exists
		ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);
	}
	return 0;
}

q_operation_t *q_op_jeq(_string_t label) {
	q_jeq_t *op = (q_jeq_t *)q_gc_malloc(sizeof(q_jeq_t));
	op->op.exec = op_jeq;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jne (jmp if not equal) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jne_t;

static int op_jne(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val1, *val2;
	q_jne_t *op = (q_jne_t *)self;
	
	if (!(val1 = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(val2 = q_peek(ctx, -1))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(is_numeric(val1) && is_numeric(val2))) {
		fprintf(stderr, "*** %s:%d illegal argument(s)\n", __func__, __LINE__);
		exit(-1);
	}
	
	if (q_value_cmp(val1, val2) != 0) {
		// TODO check label exists
		ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);
	}
	return 0;
}

q_operation_t *q_op_jne(_string_t label) {
	q_jne_t *op = (q_jne_t *)q_gc_malloc(sizeof(q_jne_t));
	op->op.exec = op_jne;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jlt (jmp if less than) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jlt_t;

static int op_jlt(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val1, *val2;
	q_jlt_t *op = (q_jlt_t *)self;
	
	if (!(val1 = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(val2 = q_peek(ctx, -1))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(is_numeric(val1) && is_numeric(val2))) {
		fprintf(stderr, "*** %s:%d illegal argument(s)\n", __func__, __LINE__);
		exit(-1);
	}
	
	if (q_value_cmp(val1, val2) < 0) {
		// TODO check label exists
		ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);
	}
	return 0;
}

q_operation_t *q_op_jlt(_string_t label) {
	q_jlt_t *op = (q_jlt_t *)q_gc_malloc(sizeof(q_jlt_t));
	op->op.exec = op_jlt;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jle (jmp if less than or equal) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jle_t;

static int op_jle(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val1, *val2;
	q_jle_t *op = (q_jle_t *)self;
	
	if (!(val1 = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(val2 = q_peek(ctx, -1))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(is_numeric(val1) && is_numeric(val2))) {
		fprintf(stderr, "*** %s:%d illegal argument(s)\n", __func__, __LINE__);
		exit(-1);
	}
	
	if (q_value_cmp(val1, val2) <= 0) {
		// TODO check label exists
		ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);
	}
	return 0;
}

q_operation_t *q_op_jle(_string_t label) {
	q_jle_t *op = (q_jle_t *)q_gc_malloc(sizeof(q_jle_t));
	op->op.exec = op_jle;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jgt (jmp if greater than) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jgt_t;

static int op_jgt(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val1, *val2;
	q_jgt_t *op = (q_jgt_t *)self;
	
	if (!(val1 = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(val2 = q_peek(ctx, -1))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(is_numeric(val1) && is_numeric(val2))) {
		fprintf(stderr, "*** %s:%d illegal argument(s)\n", __func__, __LINE__);
		exit(-1);
	}
	
	if (q_value_cmp(val1, val2) > 0) {
		// TODO check label exists
		ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);
	}
	return 0;
}

q_operation_t *q_op_jgt(_string_t label) {
	q_jgt_t *op = (q_jgt_t *)q_gc_malloc(sizeof(q_jgt_t));
	op->op.exec = op_jgt;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jge (if greater than or equal) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jge_t;

static int op_jge(q_operation_t *self, q_context_t *ctx) {
	q_value_t *val1, *val2;
	q_jge_t *op = (q_jge_t *)self;
	
	if (!(val1 = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(val2 = q_peek(ctx, -1))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	if (!(is_numeric(val1) && is_numeric(val2))) {
		fprintf(stderr, "*** %s:%d illegal argument(s)\n", __func__, __LINE__);
		exit(-1);
	}
	
	if (q_value_cmp(val1, val2) > 0) {
		// TODO check label exists
		ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);
	}
	return 0;
}

q_operation_t *q_op_jge(_string_t label) {
	q_jge_t *op = (q_jge_t *)q_gc_malloc(sizeof(q_jge_t));
	op->op.exec = op_jge;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jz (jmp if zero) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jz_t;

static int op_jz(q_operation_t *self, q_context_t *ctx) {
	q_jz_t *op = (q_jz_t *)self;
	q_value_t *val;
	
	if (!(val = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	switch(val->type) {
	case S8:
		if (!((q_s8_t *)val)->_data) return 0;
		break;
	case S16:
		if (!((q_s16_t *)val)->_data) return 0;
		break;
	case S32:
		if (!((q_s32_t *)val)->_data) return 0;
		break;
	case S64:
		if (!((q_s64_t *)val)->_data) return 0;
		break;
		
	case U8:
		if (!((q_u8_t *)val)->_data) return 0;
		break;				
	case U16:
		if (!((q_u16_t *)val)->_data) return 0;
		break;				
	case U32:
		if (!((q_u32_t *)val)->_data) return 0;
		break;				
	case U64:
		if (!((q_u64_t *)val)->_data) return 0;
		break;				
		
	case FLOAT:
		if (((q_float_t *)val)->_data == 0.0) return 0;
		break;
	case DOUBLE:
		if (((q_double_t *)val)->_data == 0.0) return 0;
		break;
						
	case STRING:
		if (((q_string_t *)val)->_data == NULL) return 0;
		break;
		
	case PTR:
	case THREAD:
		if (((q_ptr_t *)val)->_data == NULL) return 0;
		break;
	}
	
	// XXX
	ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);

	return 0;
}

q_operation_t *q_op_jz(_string_t label) {
	q_jz_t *op = (q_jz_t *)q_gc_malloc(sizeof(q_jz_t));
	op->op.exec = op_jz;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> jnz (jmp if non zero) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_jnz_t;

static int op_jnz(q_operation_t *self, q_context_t *ctx) {
	q_jnz_t *op = (q_jnz_t *)self;
	q_value_t *val;
	
	if (!(val = q_peek(ctx, 0))) {
		fprintf(stderr, "*** %s:%d stack empty\n", __func__, __LINE__);
		return -1;
	}
	
	switch(val->type) {
	case S8:
		if (((q_s8_t *)val)->_data) return 0;
		break;
	case S16:
		if (((q_s16_t *)val)->_data) return 0;
		break;
	case S32:
		if (((q_s32_t *)val)->_data) return 0;
		break;
	case S64:
		if (((q_s64_t *)val)->_data) return 0;
		break;
		
	case U8:
		if (((q_u8_t *)val)->_data) return 0;
		break;				
	case U16:
		if (((q_u16_t *)val)->_data) return 0;
		break;				
	case U32:
		if (((q_u32_t *)val)->_data) return 0;
		break;				
	case U64:
		if (((q_u64_t *)val)->_data) return 0;
		break;				
		
	case FLOAT:
		if (((q_float_t *)val)->_data != 0.0) return 0;
		break;
	case DOUBLE:
		if (((q_double_t *)val)->_data != 0.0) return 0;
		break;
						
	case STRING:
		if (((q_string_t *)val)->_data != NULL) return 0;
		break;

	case PTR:
	case THREAD:
		if (((q_ptr_t *)val)->_data != NULL) return 0;
		break;
	}
	
	// XXX
	ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);

	return 0;
}

q_operation_t *q_op_jnz(_string_t label) {
	q_jnz_t *op = (q_jnz_t *)q_gc_malloc(sizeof(q_jnz_t));
	op->op.exec = op_jnz;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> joe (jmp on error) <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_joe_t;

static int op_joe(q_operation_t *self, q_context_t *ctx) {
	q_joe_t *op = (q_joe_t *)self;
	q_err_handler_t *h = q_gc_malloc(sizeof(q_err_handler_t));
	
	h->next = ctx->err_handler;
	h->label = op->_label;
	ctx->err_handler = h;

	return 0;
}

q_operation_t *q_op_joe(_string_t label) {
	q_joe_t *op = (q_joe_t *)q_gc_malloc(sizeof(q_joe_t));
	op->op.exec = op_joe;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> clr (clear joe state) <<< */

typedef struct {
	q_operation_t op;
} q_clr_t;

static int op_clr(q_operation_t *self, q_context_t *ctx) {
	q_clr_t *op = (q_clr_t *)self;
	
	if (ctx->err_handler) { /* drop current error handler */
		ctx->err_handler = ctx->err_handler->next;
	}

	return 0;
}

// TODO use singleton
q_operation_t *q_op_clr() {
	q_clr_t *op = (q_clr_t *)q_gc_malloc(sizeof(q_clr_t));
	op->op.exec = op_clr;
	return (q_operation_t *)op;
}

