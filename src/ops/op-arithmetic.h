/* To be included by operations.c */

static inline int is_numeric(q_value_t *val) {
	return val->type > 0 && val->type <= 10;
}

/* >>> q_add_t <<< */

typedef struct {
	q_operation_t op;
} q_add_t;

static int op_add(q_operation_t *self, q_context_t *ctx) {
	q_add_t *op = (q_add_t *)self;
	q_value_t *val1, *val2;
	
	if (!(val1 = q_pop(ctx))) {
		fprintf(stderr, "*** %s: stack empty\n", __func__);
		return -1;
	}
	
	if (!(val2 = q_pop(ctx))) {
		fprintf(stderr, "*** %s: stack empty\n", __func__);
		return -1;
	}
	
	if (is_numeric(val1) && is_numeric(val2)) {
		int type = (val1->type >= val2->type) ? val1->type : val2->type;

		switch(type) {
		case S8: {
				_s8_t v1 = (val1->type == type) 
					? ((q_s8_t *)val1)->_data : to_s8(val1);
				_s8_t v2 = (val2->type == type) 
					? ((q_s8_t *)val2)->_data : to_s8(val2);
					
				q_push(ctx, (q_value_t *)q_s8(v1 + v2));
			}
			break;
		case S16: {
				_s16_t v1 = (val1->type == type) 
					? ((q_s16_t *)val1)->_data : to_s16(val1);
				_s16_t v2 = (val2->type == type) 
					? ((q_s16_t *)val2)->_data : to_s16(val2);
					
				q_push(ctx, (q_value_t *)q_s16(v1 + v2));
			}
			break;
		case S32: {
				_s32_t v1 = (val1->type == type) 
					? ((q_s32_t *)val1)->_data : to_s32(val1);
				_s32_t v2 = (val2->type == type) 
					? ((q_s32_t *)val2)->_data : to_s32(val2);
					
				q_push(ctx, (q_value_t *)q_s32(v1 + v2));
			}
			break;
		case S64: {
				_s64_t v1 = (val1->type == type) 
					? ((q_s64_t *)val1)->_data : to_s64(val1);
				_s64_t v2 = (val2->type == type) 
					? ((q_s64_t *)val2)->_data : to_s64(val2);
					
				q_push(ctx, (q_value_t *)q_s64(v1 + v2));
			}
			break;
		case U8: {
				_u8_t v1 = (val1->type == type) 
					? ((q_u8_t *)val1)->_data : to_u8(val1);
				_u8_t v2 = (val2->type == type) 
					? ((q_u8_t *)val2)->_data : to_u8(val2);
					
				q_push(ctx, (q_value_t *)q_u8(v1 + v2));
			}
			break;
		case U16: {
				_u16_t v1 = (val1->type == type) 
					? ((q_u16_t *)val1)->_data : to_u16(val1);
				_u16_t v2 = (val2->type == type) 
					? ((q_u16_t *)val2)->_data : to_u16(val2);
					
				q_push(ctx, (q_value_t *)q_u16(v1 + v2));
			}
			break;
		case U32: {
				_u32_t v1 = (val1->type == type) 
					? ((q_u32_t *)val1)->_data : to_u32(val1);
				_u32_t v2 = (val2->type == type) 
					? ((q_u32_t *)val2)->_data : to_u32(val2);
					
				q_push(ctx, (q_value_t *)q_u32(v1 + v2));
			}
			break;
		case U64: {
				_u64_t v1 = (val1->type == type) 
					? ((q_u64_t *)val1)->_data : to_u64(val1);
				_u64_t v2 = (val2->type == type) 
					? ((q_u64_t *)val2)->_data : to_u64(val2);
					
				q_push(ctx, (q_value_t *)q_u64(v1 + v2));
			}
			break;
		case FLOAT: {
				_float_t v1 = (val1->type == type) 
					? ((q_float_t *)val1)->_data : to_float(val1);
				_float_t v2 = (val2->type == type) 
					? ((q_float_t *)val2)->_data : to_float(val2);
				
				q_push(ctx, (q_value_t *)q_float(v1 + v2));
			}
			break;
		case DOUBLE: {
				_double_t v1 = (val1->type == type) 
					? ((q_double_t *)val1)->_data : to_double(val1);
				_double_t v2 = (val2->type == type) 
					? ((q_double_t *)val2)->_data : to_double(val2);
					
				q_push(ctx, (q_value_t *)q_double(v1 + v2));
			}
			break;
		default:
			// TODO report error
			return -1;
		}
	}

	return 0;
}

static q_add_t *_op_add = NULL;
q_operation_t *q_op_add(void) {
	if (_op_add == NULL) { // TODO synchronization
		_op_add = (q_add_t *)q_gc_malloc(sizeof(q_add_t));
		_op_add->op.exec = op_add;
	}
	return (q_operation_t *)_op_add;
}

/* >>> q_sub_t <<< */

typedef struct {
	q_operation_t op;
} q_sub_t;

static int op_sub(q_operation_t *self, q_context_t *ctx) {
	q_sub_t *op = (q_sub_t *)self;
	q_value_t *val1, *val2;
	
	if (!(val1 = q_pop(ctx))) {
		fprintf(stderr, "*** %s: stack empty\n", __func__);
		return -1;
	}
	
	if (!(val2 = q_pop(ctx))) {
		fprintf(stderr, "*** %s: stack empty\n", __func__);
		return -1;
	}
	
	if (is_numeric(val1) && is_numeric(val2)) {
		int type = (val1->type >= val2->type) ? val1->type : val2->type;

		switch(type) {
		case S8: {
				_s8_t v1 = (val1->type == type) 
					? ((q_s8_t *)val1)->_data : to_s8(val1);
				_s8_t v2 = (val2->type == type) 
					? ((q_s8_t *)val2)->_data : to_s8(val2);
					
				q_push(ctx, (q_value_t *)q_s8(v2 - v1));
			}
			break;
		case S16: {
				_s16_t v1 = (val1->type == type) 
					? ((q_s16_t *)val1)->_data : to_s16(val1);
				_s16_t v2 = (val2->type == type) 
					? ((q_s16_t *)val2)->_data : to_s16(val2);
					
				q_push(ctx, (q_value_t *)q_s16(v2 - v1));
			}
			break;
		case S32: {
				_s32_t v1 = (val1->type == type) 
					? ((q_s32_t *)val1)->_data : to_s32(val1);
				_s32_t v2 = (val2->type == type) 
					? ((q_s32_t *)val2)->_data : to_s32(val2);
					
				q_push(ctx, (q_value_t *)q_s32(v2 - v1));
			}
			break;
		case S64: {
				_s64_t v1 = (val1->type == type) 
					? ((q_s64_t *)val1)->_data : to_s64(val1);
				_s64_t v2 = (val2->type == type) 
					? ((q_s64_t *)val2)->_data : to_s64(val2);
					
				q_push(ctx, (q_value_t *)q_s64(v2 - v1));
			}
			break;
		case U8: {
				_u8_t v1 = (val1->type == type) 
					? ((q_u8_t *)val1)->_data : to_u8(val1);
				_u8_t v2 = (val2->type == type) 
					? ((q_u8_t *)val2)->_data : to_u8(val2);
					
				q_push(ctx, (q_value_t *)q_u8(v2 - v1));
			}
			break;
		case U16: {
				_u16_t v1 = (val1->type == type) 
					? ((q_u16_t *)val1)->_data : to_u16(val1);
				_u16_t v2 = (val2->type == type) 
					? ((q_u16_t *)val2)->_data : to_u16(val2);
					
				q_push(ctx, (q_value_t *)q_u16(v2 - v1));
			}
			break;
		case U32: {
				_u32_t v1 = (val1->type == type) 
					? ((q_u32_t *)val1)->_data : to_u32(val1);
				_u32_t v2 = (val2->type == type) 
					? ((q_u32_t *)val2)->_data : to_u32(val2);
					
				q_push(ctx, (q_value_t *)q_u32(v2 - v1));
			}
			break;
		case U64: {
				_u64_t v1 = (val1->type == type) 
					? ((q_u64_t *)val1)->_data : to_u64(val1);
				_u64_t v2 = (val2->type == type) 
					? ((q_u64_t *)val2)->_data : to_u64(val2);
					
				q_push(ctx, (q_value_t *)q_u64(v2 - v1));
			}
			break;
		case FLOAT: {
				_float_t v1 = (val1->type == type) 
					? ((q_float_t *)val1)->_data : to_float(val1);
				_float_t v2 = (val2->type == type) 
					? ((q_float_t *)val2)->_data : to_float(val2);
					
				q_push(ctx, (q_value_t *)q_float(v2 - v1));
			}
			break;
		case DOUBLE: {
				_double_t v1 = (val1->type == type) 
					? ((q_double_t *)val1)->_data : to_double(val1);
				_double_t v2 = (val2->type == type) 
					? ((q_double_t *)val2)->_data : to_double(val2);
					
				q_push(ctx, (q_value_t *)q_double(v2 - v1));
			}
			break;
		default:
			// TODO report error
			return -1;
		}
	}

	return 0;
}

static q_sub_t *_op_sub = NULL;
q_operation_t *q_op_sub(void) {
	if (_op_sub == NULL) { // TODO synchronization
		_op_sub = (q_sub_t *)q_gc_malloc(sizeof(q_sub_t));
		_op_sub->op.exec = op_sub;
	}
	return (q_operation_t *)_op_sub;
}

/* >>> q_mul_t <<< */

typedef struct {
	q_operation_t op;
} q_mul_t;

static int op_mul(q_operation_t *self, q_context_t *ctx) {
	q_mul_t *op = (q_mul_t *)self;
	q_value_t *val1, *val2;
	
	if (!(val1 = q_pop(ctx))) {
		fprintf(stderr, "*** %s: stack empty\n", __func__);
		return -1;
	}
	
	if (!(val2 = q_pop(ctx))) {
		fprintf(stderr, "*** %s: stack empty\n", __func__);
		return -1;
	}
	
	if (is_numeric(val1) && is_numeric(val2)) {
		int type = (val1->type >= val2->type) ? val1->type : val2->type;

		switch(type) {
		case S8: {
				_s8_t v1 = (val1->type == type) 
					? ((q_s8_t *)val1)->_data : to_s8(val1);
				_s8_t v2 = (val2->type == type) 
					? ((q_s8_t *)val2)->_data : to_s8(val2);
					
				q_push(ctx, (q_value_t *)q_s8(v1 * v2));
			}
			break;
		case S16: {
				_s16_t v1 = (val1->type == type) 
					? ((q_s16_t *)val1)->_data : to_s16(val1);
				_s16_t v2 = (val2->type == type) 
					? ((q_s16_t *)val2)->_data : to_s16(val2);
					
				q_push(ctx, (q_value_t *)q_s16(v1 * v2));
			}
			break;
		case S32: {
				_s32_t v1 = (val1->type == type) 
					? ((q_s32_t *)val1)->_data : to_s32(val1);
				_s32_t v2 = (val2->type == type) 
					? ((q_s32_t *)val2)->_data : to_s32(val2);
					
				q_push(ctx, (q_value_t *)q_s32(v1 * v2));
			}
			break;
		case S64: {
				_s64_t v1 = (val1->type == type) 
					? ((q_s64_t *)val1)->_data : to_s64(val1);
				_s64_t v2 = (val2->type == type) 
					? ((q_s64_t *)val2)->_data : to_s64(val2);
					
				q_push(ctx, (q_value_t *)q_s64(v1 * v2));
			}
			break;
		case U8: {
				_u8_t v1 = (val1->type == type) 
					? ((q_u8_t *)val1)->_data : to_u8(val1);
				_u8_t v2 = (val2->type == type) 
					? ((q_u8_t *)val2)->_data : to_u8(val2);
					
				q_push(ctx, (q_value_t *)q_u8(v1 * v2));
			}
			break;
		case U16: {
				_u16_t v1 = (val1->type == type) 
					? ((q_u16_t *)val1)->_data : to_u16(val1);
				_u16_t v2 = (val2->type == type) 
					? ((q_u16_t *)val2)->_data : to_u16(val2);
					
				q_push(ctx, (q_value_t *)q_u16(v1 * v2));
			}
			break;
		case U32: {
				_u32_t v1 = (val1->type == type) 
					? ((q_u32_t *)val1)->_data : to_u32(val1);
				_u32_t v2 = (val2->type == type) 
					? ((q_u32_t *)val2)->_data : to_u32(val2);
					
				q_push(ctx, (q_value_t *)q_u32(v1 * v2));
			}
			break;
		case U64: {
				_u64_t v1 = (val1->type == type) 
					? ((q_u64_t *)val1)->_data : to_u64(val1);
				_u64_t v2 = (val2->type == type) 
					? ((q_u64_t *)val2)->_data : to_u64(val2);
					
				q_push(ctx, (q_value_t *)q_u64(v1 * v2));
			}
			break;
		case FLOAT: {
				_float_t v1 = (val1->type == type) 
					? ((q_float_t *)val1)->_data : to_float(val1);
				_float_t v2 = (val2->type == type) 
					? ((q_float_t *)val2)->_data : to_float(val2);
					
				q_push(ctx, (q_value_t *)q_float(v1 * v2));
			}
			break;
		case DOUBLE: {
				_double_t v1 = (val1->type == type) 
					? ((q_double_t *)val1)->_data : to_double(val1);
				_double_t v2 = (val2->type == type) 
					? ((q_double_t *)val2)->_data : to_double(val2);
					
				q_push(ctx, (q_value_t *)q_double(v1 * v2));
			}
			break;
		default:
			// TODO report error
			return -1;
		}
	}

	return 0;
}

static q_mul_t *_op_mul = NULL;
q_operation_t *q_op_mul(void) {
	if (_op_mul == NULL) { // TODO synchronization
		_op_mul = (q_mul_t *)q_gc_malloc(sizeof(q_mul_t));
		_op_mul->op.exec = op_mul;
	}
	return (q_operation_t *)_op_mul;
}

/* >>> q_div_t <<< */

typedef struct {
	q_operation_t op;
} q_div_t;

static int op_div(q_operation_t *self, q_context_t *ctx) {
	q_div_t *op = (q_div_t *)self;
	q_value_t *val1, *val2;
	
	if (!(val1 = q_pop(ctx))) {
		return ERROR_VALUE_IS_NULL;
	}
	
	if (!(val2 = q_pop(ctx))) {
		return ERROR_VALUE_IS_NULL;
	}
	
	if (is_numeric(val1) && is_numeric(val2)) {
		int type = (val1->type >= val2->type) ? val1->type : val2->type;

		switch(type) {
		case S8: {
				_s8_t v1 = (val1->type == type) 
					? ((q_s8_t *)val1)->_data : to_s8(val1);
				_s8_t v2 = (val2->type == type) 
					? ((q_s8_t *)val2)->_data : to_s8(val2);
				
				if (v1 != 0) 
					q_push(ctx, (q_value_t *)q_s8(v2 / v1));
				else 
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case S16: {
				_s16_t v1 = (val1->type == type) 
					? ((q_s16_t *)val1)->_data : to_s16(val1);
				_s16_t v2 = (val2->type == type) 
					? ((q_s16_t *)val2)->_data : to_s16(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_s16(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case S32: {
				_s32_t v1 = (val1->type == type) 
					? ((q_s32_t *)val1)->_data : to_s32(val1);
				_s32_t v2 = (val2->type == type) 
					? ((q_s32_t *)val2)->_data : to_s32(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_s32(v2 / v1));
				else 
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case S64: {
				_s64_t v1 = (val1->type == type) 
					? ((q_s64_t *)val1)->_data : to_s64(val1);
				_s64_t v2 = (val2->type == type) 
					? ((q_s64_t *)val2)->_data : to_s64(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_s64(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case U8: {
				_u8_t v1 = (val1->type == type) 
					? ((q_u8_t *)val1)->_data : to_u8(val1);
				_u8_t v2 = (val2->type == type) 
					? ((q_u8_t *)val2)->_data : to_u8(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_u8(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case U16: {
				_u16_t v1 = (val1->type == type) 
					? ((q_u16_t *)val1)->_data : to_u16(val1);
				_u16_t v2 = (val2->type == type) 
					? ((q_u16_t *)val2)->_data : to_u16(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_u16(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case U32: {
				_u32_t v1 = (val1->type == type) 
					? ((q_u32_t *)val1)->_data : to_u32(val1);
				_u32_t v2 = (val2->type == type) 
					? ((q_u32_t *)val2)->_data : to_u32(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_u32(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case U64: {
				_u64_t v1 = (val1->type == type) 
					? ((q_u64_t *)val1)->_data : to_u64(val1);
				_u64_t v2 = (val2->type == type) 
					? ((q_u64_t *)val2)->_data : to_u64(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_u64(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case FLOAT: {
				_float_t v1 = (val1->type == type) 
					? ((q_float_t *)val1)->_data : to_float(val1);
				_float_t v2 = (val2->type == type) 
					? ((q_float_t *)val2)->_data : to_float(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_float(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		case DOUBLE: {
				_double_t v1 = (val1->type == type) 
					? ((q_double_t *)val1)->_data : to_double(val1);
				_double_t v2 = (val2->type == type) 
					? ((q_double_t *)val2)->_data : to_double(val2);
					
				if (v1 != 0)
					q_push(ctx, (q_value_t *)q_double(v2 / v1));
				else
					return ERROR_DIVISION_BY_ZERO;
			}
			break;
		default:
			return ERROR_ILLIGAL_ARGUMENT;
		}
	}

	return 0;
}

static q_div_t *_op_div = NULL;
q_operation_t *q_op_div(void) {
	if (_op_div == NULL) { // TODO synchronization
		_op_div = (q_div_t *)q_gc_malloc(sizeof(q_div_t));
		_op_div->op.exec = op_div;
	}
	return (q_operation_t *)_op_div;
}
