/* To be included by operations.c */

/* >>> convertions <<< */

static _s32_t _strtol(q_string_t *val) {
	int base;
	char *data = val->_data, *end;
	
	while(*data && !isdigit(*data))
		++data;
	
	if (*data == '0' && *(data + 1) == 'x') {
		data += 2;
		base = 16;
	} else {
		base = 10;
	}
	
	errno = 0; /* yes, errno is thread safe */
	_s32_t result = strtol(data, &end, base);
	return ((end == data) || (errno != 0)) ? 0L : result;
}

static _s64_t _strtoll(q_string_t *val) {
	int base;
	char *data = val->_data, *end;
	
	while(*data && !isdigit(*data))
		++data;
	
	if (*data == '0' && *(data + 1) == 'x') {
		data += 2;
		base = 16;
	} else {
		base = 10;
	}
	
	errno = 0; /* yes, errno is thread safe */
	_s64_t result = strtoll(data, &end, base);
	return ((end == data) || (errno != 0)) ? 0L : result;
}

static _u32_t _strtoul(q_string_t *val) {
	int base;
	char *data = val->_data, *end;
	
	while(*data && !isdigit(*data))
		++data;
	
	if (*data == '0' && *(data + 1) == 'x') {
		data += 2;
		base = 16;
	} else {
		base = 10;
	}
	
	errno = 0; /* yes, errno is thread safe */
	_u32_t result = strtoul(data, &end, base);
	return ((end == data) || (errno != 0)) ? 0L : result;
}

static _u64_t _strtoull(q_string_t *val) {
	int base;
	char *data = val->_data, *end;
	
	while(*data && !isdigit(*data))
		++data;
	
	if (*data == '0' && *(data + 1) == 'x') {
		data += 2;
		base = 16;
	} else {
		base = 10;
	}
	
	errno = 0; /* yes, errno is thread safe */
	_u64_t result = strtoull(data, &end, base);
	return ((end == data) || (errno != 0)) ? 0L : result;
}

static _float_t _strtof(q_string_t *val) {
	char *end;
	errno = 0; /* yes, errno is thread safe */
	_float_t result = strtof(val->_data, &end);
	return ((end == val->_data) || (errno != 0)) ? NAN : result;
}

static _double_t _strtod(q_string_t *val) {
	char *end;
	errno = 0; /* yes, errno is thread safe */
	_double_t result = strtod(val->_data, &end);
	return ((end == val->_data) || (errno != 0)) ? NAN : result;
}

static _s8_t to_s8(q_value_t *val) {
	_s8_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_s8_t)((q_s8_t *)val)->_data);
	case S16:
		return ((_s8_t)((q_s16_t *)val)->_data);
	case S32:
		return ((_s8_t)((q_s32_t *)val)->_data);
	case S64:
		return ((_s8_t)((q_s64_t *)val)->_data);
	case U8:
		return ((_s8_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_s8_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_s8_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_s8_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_s8_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_s8_t)((q_double_t *)val)->_data);
	case STRING:
		return (_s8_t)_strtol((q_string_t *)val);
	default:
		return 0;
	}
}

static _s16_t to_s16(q_value_t *val) {
	_s16_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_s16_t)((q_s8_t *)val)->_data);
	case S16:
		return ((_s16_t)((q_s16_t *)val)->_data);
	case S32:
		return ((_s16_t)((q_s32_t *)val)->_data);
	case S64:
		return ((_s16_t)((q_s64_t *)val)->_data);
	case U8:
		return ((_s16_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_s16_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_s16_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_s16_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_s16_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_s16_t)((q_double_t *)val)->_data);
	case STRING:
		return (_s16_t)_strtol((q_string_t *)val);
	default:
		return 0;
	}
}

static _s32_t to_s32(q_value_t *val) {
	_s32_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_s32_t)((q_s8_t *)val)->_data);
	case S16:
		return ((_s32_t)((q_s16_t *)val)->_data);
	case S32:
		return ((_s32_t)((q_s32_t *)val)->_data);
	case S64:
		return ((_s32_t)((q_s64_t *)val)->_data);
	case U8:
		return ((_s32_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_s32_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_s32_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_s32_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_s32_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_s32_t)((q_double_t *)val)->_data);
	case STRING:
		return (_s32_t)_strtol((q_string_t *)val);
	default:
		return 0;
	}
}

static _s64_t to_s64(q_value_t *val) {
	_s64_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_s64_t)((q_s8_t *)val)->_data);
	case S16:
		return ((_s64_t)((q_s16_t *)val)->_data);
	case S32:
		return ((_s64_t)((q_s32_t *)val)->_data);
	case S64:
		return ((_s64_t)((q_s64_t *)val)->_data);
	case U8:
		return ((_s64_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_s64_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_s64_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_s64_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_s64_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_s64_t)((q_double_t *)val)->_data);
	case STRING:
		return (_s64_t)_strtoll((q_string_t *)val);
	default:
		return 0;
	}
}

static _u8_t to_u8(q_value_t *val) {
	_u8_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_u8_t)((q_u8_t *)val)->_data);
	case S16:
		return ((_u8_t)((q_u16_t *)val)->_data);
	case S32:
		return ((_u8_t)((q_u32_t *)val)->_data);
	case S64:
		return ((_u8_t)((q_u64_t *)val)->_data);
	case U8:
		return ((_u8_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_u8_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_u8_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_u8_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_u8_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_u8_t)((q_double_t *)val)->_data);
	case STRING:
		return (_u8_t)_strtoul((q_string_t *)val);
	default:
		return 0;
	}
}

static _u16_t to_u16(q_value_t *val) {
	_u16_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_u16_t)((q_u8_t *)val)->_data);
	case S16:
		return ((_u16_t)((q_u16_t *)val)->_data);
	case S32:
		return ((_u16_t)((q_u32_t *)val)->_data);
	case S64:
		return ((_u16_t)((q_u64_t *)val)->_data);
	case U8:
		return ((_u16_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_u16_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_u16_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_u16_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_u16_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_u16_t)((q_double_t *)val)->_data);
	case STRING:
		return (_u16_t)_strtoul((q_string_t *)val);
	default:
		return 0;
	}
}

static _u32_t to_u32(q_value_t *val) {
	_u32_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_u32_t)((q_s8_t *)val)->_data);
	case S16:
		return ((_u32_t)((q_s16_t *)val)->_data);
	case S32:
		return ((_u32_t)((q_s32_t *)val)->_data);
	case S64:
		return ((_u32_t)((q_s64_t *)val)->_data);
	case U8:
		return ((_u32_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_u32_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_u32_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_u32_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_u32_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_u32_t)((q_double_t *)val)->_data);
	case STRING:
		return (_u32_t)_strtoul((q_string_t *)val);
	default:
		return 0;
	}
}

static _u64_t to_u64(q_value_t *val) {
	_u64_t data;
	
	if (!val) 
		return 0;
	
	switch(val->type) {
	case S8:
		return ((_u64_t)((q_s8_t *)val)->_data);
	case S16:
		return ((_u64_t)((q_s16_t *)val)->_data);
	case S32:
		return ((_u64_t)((q_s32_t *)val)->_data);
	case S64:
		return ((_u64_t)((q_s64_t *)val)->_data);
	case U8:
		return ((_u64_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_u64_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_u64_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_u64_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((_u64_t)((q_float_t *)val)->_data);
	case DOUBLE:
		return ((_u64_t)((q_double_t *)val)->_data);
	case STRING:
		return (_u64_t)_strtoll((q_string_t *)val);
	default:
		return 0;
	}
}

static _float_t to_float(q_value_t *val) {
	_float_t data;
	
	if (!val) 
		return NAN;
	
	switch(val->type) {
	case S8:
		return ((_float_t)((q_s8_t *)val)->_data);
	case S16:
		return ((_float_t)((q_s16_t *)val)->_data);
	case S32:
		return ((_float_t)((q_s32_t *)val)->_data);
	case S64:
		return ((_float_t)((q_s64_t *)val)->_data);
	case U8:
		return ((_float_t)((q_u8_t *)val)->_data);
	case U16:
		return ((_float_t)((q_u16_t *)val)->_data);
	case U32:
		return ((_float_t)((q_u32_t *)val)->_data);
	case U64:
		return ((_float_t)((q_u64_t *)val)->_data);
	case FLOAT:
		return ((q_float_t *)val)->_data;
	case DOUBLE:
		return ((_float_t)((q_double_t *)val)->_data);
	case STRING:
		return _strtof((q_string_t *)val);
	default:
		return NAN;
	}
}

static _double_t to_double(q_value_t *val) {
	if (!val) 
		return NAN;
	
	switch(val->type) {
	case S8:
		return (_double_t)(((q_s8_t *)val)->_data);
	case S16:
		return (_double_t)(((q_s16_t *)val)->_data);
	case S32:
		return (_double_t)(((q_s32_t *)val)->_data);
	case S64:
		return (_double_t)(((q_s64_t *)val)->_data);
	case U8:
		return (_double_t)(((q_u8_t *)val)->_data);
	case U16:
		return (_double_t)(((q_u16_t *)val)->_data);
	case U32:
		return (_double_t)(((q_u32_t *)val)->_data);
	case U64:
		return (_double_t)(((q_u64_t *)val)->_data);
	case FLOAT:
		return (_double_t)(((q_float_t *)val)->_data);
	case DOUBLE:
		return ((q_double_t *)val)->_data;
	case STRING:
		return _strtod((q_string_t *)val);
	default:
		return NAN;
	}
}

/* >>> q_cnvto_s8_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_s8_t;

static int op_cnvto_s8(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s8(to_s8(q_pop(ctx))));
	return 0;
}

static q_cnvto_s8_t *_op_cnvto_s8 = NULL;
q_operation_t *q_op_cnvto_s8(void) {
	if (_op_cnvto_s8 == NULL) { // TODO synchronization
		_op_cnvto_s8 = (q_cnvto_s8_t *)q_gc_malloc(sizeof(q_cnvto_s8_t));
		_op_cnvto_s8->op.exec = op_cnvto_s8;
	}
	return (q_operation_t *)_op_cnvto_s8;
}

/* >>> q_cnvto_s16_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_s16_t;

static int op_cnvto_s16(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s16(to_s16(q_pop(ctx))));
	return 0;
}

static q_cnvto_s16_t *_op_cnvto_s16 = NULL;
q_operation_t *q_op_cnvto_s16(void) {
	if (_op_cnvto_s16 == NULL) { // TODO synchronization
		_op_cnvto_s16 = (q_cnvto_s16_t *)q_gc_malloc(sizeof(q_cnvto_s16_t));
		_op_cnvto_s16->op.exec = op_cnvto_s16;
	}
	return (q_operation_t *)_op_cnvto_s16;
}

/* >>> q_cnvto_s32_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_s32_t;

static int op_cnvto_s32(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s32(to_s32(q_pop(ctx))));
	return 0;
}

static q_cnvto_s32_t *_op_cnvto_s32 = NULL;
q_operation_t *q_op_cnvto_s32(void) {
	if (_op_cnvto_s32 == NULL) { // TODO synchronization
		_op_cnvto_s32 = (q_cnvto_s32_t *)q_gc_malloc(sizeof(q_cnvto_s32_t));
		_op_cnvto_s32->op.exec = op_cnvto_s32;
	}
	return (q_operation_t *)_op_cnvto_s32;
}

/* >>> q_cnvto_s64_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_s64_t;

static int op_cnvto_s64(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_s64(to_s64(q_pop(ctx))));
	return 0;
}

static q_cnvto_s64_t *_op_cnvto_s64 = NULL;
q_operation_t *q_op_cnvto_s64(void) {
	if (_op_cnvto_s64 == NULL) { // TODO synchronization
		_op_cnvto_s64 = (q_cnvto_s64_t *)q_gc_malloc(sizeof(q_cnvto_s64_t));
		_op_cnvto_s64->op.exec = op_cnvto_s64;
	}
	return (q_operation_t *)_op_cnvto_s64;
}

/* >>> q_cnvto_u8_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_u8_t;

static int op_cnvto_u8(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u8(to_u8(q_pop(ctx))));
	return 0;
}

static q_cnvto_u8_t *_op_cnvto_u8 = NULL;
q_operation_t *q_op_cnvto_u8(void) {
	if (_op_cnvto_u8 == NULL) { // TODO synchronization
		_op_cnvto_u8 = (q_cnvto_u8_t *)q_gc_malloc(sizeof(q_cnvto_u8_t));
		_op_cnvto_u8->op.exec = op_cnvto_u8;
	}
	return (q_operation_t *)_op_cnvto_u8;
}

/* >>> q_cnvto_u16_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_u16_t;

static int op_cnvto_u16(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u16(to_u16(q_pop(ctx))));
	return 0;
}

static q_cnvto_u16_t *_op_cnvto_u16 = NULL;
q_operation_t *q_op_cnvto_u16(void) {
	if (_op_cnvto_u16 == NULL) { // TODO synchronization
		_op_cnvto_u16 = (q_cnvto_u16_t *)q_gc_malloc(sizeof(q_cnvto_u16_t));
		_op_cnvto_u16->op.exec = op_cnvto_u16;
	}
	return (q_operation_t *)_op_cnvto_u16;
}

/* >>> q_cnvto_u32_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_u32_t;

static int op_cnvto_u32(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u32(to_u32(q_pop(ctx))));
	return 0;
}

static q_cnvto_u32_t *_op_cnvto_u32 = NULL;
q_operation_t *q_op_cnvto_u32(void) {
	if (_op_cnvto_u32 == NULL) { // TODO synchronization
		_op_cnvto_u32 = (q_cnvto_u32_t *)q_gc_malloc(sizeof(q_cnvto_u32_t));
		_op_cnvto_u32->op.exec = op_cnvto_u32;
	}
	return (q_operation_t *)_op_cnvto_u32;
}

/* >>> q_cnvto_u64_t <<< */

typedef struct {
	q_operation_t op;
} q_cnvto_u64_t;

static int op_cnvto_u64(q_operation_t *self, q_context_t *ctx) {
	q_push(ctx, (q_value_t *)q_u64(to_u64(q_pop(ctx))));
	return 0;
}

static q_cnvto_u64_t *_op_cnvto_u64 = NULL;
q_operation_t *q_op_cnvto_u64(void) {
	if (_op_cnvto_u64 == NULL) { // TODO synchronization
		_op_cnvto_u64 = (q_cnvto_u64_t *)q_gc_malloc(sizeof(q_cnvto_u64_t));
		_op_cnvto_u64->op.exec = op_cnvto_u64;
	}
	return (q_operation_t *)_op_cnvto_u64;
}

