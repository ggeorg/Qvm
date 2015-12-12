/* To be included by operations.c */

/* >>> q_call_t <<< */

typedef struct {
	q_operation_t op;
	_string_t _label;
} q_call_t;

static int op_call(q_operation_t *self, q_context_t *ctx) {
	q_call_t *op = (q_call_t *)self;	
	q_trace_t *t = q_gc_malloc(sizeof(q_trace_t));
	
	t->next = ctx->trace;
	t->pc = ctx->pc;
	
	ctx->trace = t;
	
	// TODO check label existance
	ctx->pc = (size_t)g_hash_table_lookup(ctx->vm->lhash, op->_label);

	return 0;
}

q_operation_t *q_op_call(_string_t label) {
	q_call_t *op = (q_call_t *)q_gc_malloc(sizeof(q_call_t));
	op->op.exec = op_call;
	op->_label = label;
	return (q_operation_t *)op;
}

/* >>> q_ret_t <<< */

typedef struct {
	q_operation_t op;
} q_ret_t;

static int op_ret(q_operation_t *self, q_context_t *ctx) {
	q_ret_t *op = (q_ret_t *)self;
	q_trace_t *t = ctx->trace;
	
	if (t) {
		ctx->trace = t->next;
		ctx->pc = t->pc;
	} else {
		return OP_EXIT;
	}
	
	return OP_OK;
}

static q_ret_t *_op_ret = NULL;
q_operation_t *q_op_ret(void) {
	if (_op_ret == NULL) { // TODO synchronization
		_op_ret = (q_ret_t *)q_gc_malloc(sizeof(q_ret_t));
		_op_ret->op.exec = op_ret;
	}
	return (q_operation_t *)_op_ret;
}

/* >>> q_invoke_t <<< */

typedef struct {
	q_operation_t op;
	_string_t _mod;
	_string_t _sym;
	gboolean _void;
} q_invoke_t;

static int op_invoke(q_operation_t *self, q_context_t *ctx) {
	GModule *mod;
	q_value_t *_argc;
	q_invoke_t *op = (q_invoke_t *)self;

	mod = (GModule *)g_hash_table_lookup(ctx->vm->mhash, op->_mod);	
	if (mod) {
		_argc = q_pop(ctx);
		if (_argc && _argc->type == S8) {
			int argc = ((q_s8_t *)_argc)->_data, i;
			
			ffi_cif cif;
			ffi_type *arg_types[argc];
			void *arg_values[argc];
			ffi_status status;
			ffi_type *result_type;
			
			q_value_t *args[argc];
			
			i = 0;
			while (i < argc) {
				args[i] = q_pop(ctx);
				switch(args[i]->type) {
				case S8:
					arg_types[i] = &ffi_type_sint8;
					arg_values[i] = &(((q_s8_t *)args[i])->_data);
					break;
				case S16:
					arg_types[i] = &ffi_type_sint16;
					arg_values[i] = &(((q_s16_t *)args[i])->_data);
					break;
				case S32:
					arg_types[i] = &ffi_type_sint32;
					arg_values[i] = &(((q_s32_t *)args[i])->_data);
					break;
				case S64:
					arg_types[i] = &ffi_type_sint64;
					arg_values[i] = &(((q_s64_t *)args[i])->_data);
					break;

				case U8:
					arg_types[i] = &ffi_type_uint8;
					arg_values[i] = &(((q_u8_t *)args[i])->_data);
					break;
				case U16:
					arg_types[i] = &ffi_type_uint16;
					arg_values[i] = &(((q_u16_t *)args[i])->_data);
					break;
				case U32:
					arg_types[i] = &ffi_type_uint32;
					arg_values[i] = &(((q_u32_t *)args[i])->_data);
					break;
				case U64:
					arg_types[i] = &ffi_type_uint64;
					arg_values[i] = &(((q_u64_t *)args[i])->_data);
					break;
					
				case FLOAT:
					arg_types[i] = &ffi_type_float;
					arg_values[i] = &(((q_float_t *)args[i])->_data);
					break;
				case DOUBLE:
					arg_types[i] = &ffi_type_double;
					arg_values[i] = &(((q_double_t *)args[i])->_data);
					break;

				case STRING:
					arg_types[i] = &ffi_type_pointer;
					arg_values[i] = &(((q_string_t *)args[i])->_data);
					break;
					
				}
				++i;
			}

			q_value_t *ret = q_pop(ctx);
			switch(ret->type) {
			case S8:
				result_type = &ffi_type_sint8;
				break;
			case S16:
				result_type = &ffi_type_sint16;
				break;
			case S32:
				result_type = &ffi_type_sint32;
				break;
			case S64:
				result_type = &ffi_type_sint64;
				break;
				
			case U8:
				result_type = &ffi_type_uint8;
				break;				
			case U16:
				result_type = &ffi_type_uint16;
				break;				
			case U32:
				result_type = &ffi_type_uint32;
				break;				
			case U64:
				result_type = &ffi_type_uint64;
				break;				
				
			case FLOAT:
				result_type = &ffi_type_float;
				break;
			case DOUBLE:
				result_type = &ffi_type_double;
				break;
								
			case STRING:
				result_type = &ffi_type_pointer;
				break;

			}
			
			if ((status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 
					argc, result_type, arg_types)) != FFI_OK) {
				// Handle the ffi_status error
				fprintf(stderr, "FFI STATUS ERROR\n");
				exit(-1);
			}

			void (*fcn)(void);
			if (g_module_symbol(mod, op->_sym, (gpointer *)&fcn)) {
				switch(ret->type) {
				case S8: {
						q_s8_t *result = (q_s8_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				case S16: {
						q_s16_t *result = (q_s16_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				case S32: {
						q_s32_t *result = (q_s32_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				case S64: {
						q_s64_t *result = (q_s64_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
					
				case U8: {
						q_u8_t *result = (q_u8_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				case U16: {
						q_u16_t *result = (q_u16_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				case U32: {
						q_u32_t *result = (q_u32_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				case U64: {
						q_u64_t *result = (q_u64_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
					
				case FLOAT: {
						q_float_t *result = (q_float_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				case DOUBLE: {
						q_double_t *result = (q_double_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
					
				case STRING: {
						q_string_t *result = (q_string_t *)ret;
						ffi_call(&cif, fcn, &(result->_data), arg_values);
						q_push(ctx, ret);
					}
					break;
				}
			} else {
				fprintf(stderr, "TODO symbol %s not found exception\n", op->_mod);
				exit(1);
			}
		}

	} else {
		fprintf(stderr, "TODO module %s not found exception\n", op->_mod);
		exit(1);
	}
	return 0;
}

q_operation_t *q_op_invoke(_string_t mod, _string_t sym) {
	q_invoke_t *op = (q_invoke_t *)q_gc_malloc(sizeof(q_invoke_t));
	op->op.exec = op_invoke;
	op->_mod = mod;
	op->_sym = sym;
	op->_void = FALSE;
	return (q_operation_t *)op;
}

q_operation_t *q_op_invoke_void(_string_t mod, _string_t sym) {
	q_invoke_t *op = (q_invoke_t *)q_gc_malloc(sizeof(q_invoke_t));
	op->op.exec = op_invoke;
	op->_mod = mod;
	op->_sym = sym;
	op->_void = TRUE;
	return (q_operation_t *)op;
}
