#ifndef QVM_OPERATIONS_H
#define QVM_OPERATIONS_H

#include "_types.h"

/* >>> push <<< */

q_operation_t *q_op_push_s8(_s8_t val);
q_operation_t *q_op_push_s16(_s16_t val);
q_operation_t *q_op_push_s32(_s32_t val);
q_operation_t *q_op_push_s64(_s64_t val);

q_operation_t *q_op_push_u8(_u8_t val);
q_operation_t *q_op_push_u16(_u16_t val);
q_operation_t *q_op_push_u32(_u32_t val);
q_operation_t *q_op_push_u64(_u64_t val);

q_operation_t *q_op_push_float(_float_t val);
q_operation_t *q_op_push_double(_double_t val);

q_operation_t *q_op_push_string(_string_t val);
q_operation_t *q_op_push_ptr(_ptr_t val);

q_operation_t *q_op_push(_string_t var);

/* >>> stack manipulation <<< */

q_operation_t *q_op_pop(void);
q_operation_t *q_op_pop_n(_s8_t val);
q_operation_t *q_op_pop_v(_string_t var);

q_operation_t *q_op_rot();
q_operation_t *q_op_rot_n(_s8_t val);

/* >>> data convertion <<< */

q_operation_t *q_op_cnvto_s8(void);
q_operation_t *q_op_cnvto_s16(void);
q_operation_t *q_op_cnvto_s32(void);
q_operation_t *q_op_cnvto_s64(void);

q_operation_t *q_op_cnvto_u8(void);
q_operation_t *q_op_cnvto_u16(void);
q_operation_t *q_op_cnvto_u32(void);
q_operation_t *q_op_cnvto_u64(void);

/* >>> arithmetic <<< */

q_operation_t *q_op_add(void);
q_operation_t *q_op_sub(void);
q_operation_t *q_op_mul(void);
q_operation_t *q_op_div(void);

/* >>> branching and conditionals <<< */

q_operation_t *q_op_jmp(_string_t label);

q_operation_t *q_op_jeq(_string_t label);
q_operation_t *q_op_jne(_string_t label);
q_operation_t *q_op_jlt(_string_t label);
q_operation_t *q_op_jle(_string_t label);
q_operation_t *q_op_jgt(_string_t label);
q_operation_t *q_op_jge(_string_t label);

q_operation_t *q_op_jz(_string_t label);
q_operation_t *q_op_jnz(_string_t label);

q_operation_t *q_op_jn(_string_t label);
q_operation_t *q_op_jp(_string_t label);

q_operation_t *q_op_joe(_string_t label);
q_operation_t *q_op_clr(void);

/* >>> subroutines <<< */

q_operation_t *q_op_call(_string_t label);
q_operation_t *q_op_ret(void);

q_operation_t *q_op_run(_string_t label);

q_operation_t *q_op_invoke(_string_t mod, _string_t sym);
q_operation_t *q_op_invoke_void(_string_t mod, _string_t sym);

/* >>> threads <<< */




/* >>> print & dump <<< */

q_operation_t *q_op_dump(void);
q_operation_t *q_op_print(void);

#endif
