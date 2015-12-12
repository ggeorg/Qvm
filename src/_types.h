#ifndef QVM_TYPES_H
#define QVM_TYPES_H

#include <stdlib.h>

#include "Qvm.h"
#include "qvm-gc.h"

/* >>> signed <<< */

typedef struct {
	q_value_t value;
	_s8_t _data;
} q_s8_t;

typedef struct {
	q_value_t value;
	_s16_t _data;
} q_s16_t;

typedef struct {
	q_value_t value;
	_s32_t _data;
} q_s32_t;

typedef struct {
	q_value_t value;
	_s64_t _data;
} q_s64_t;

/* >>> unsigned <<< */

typedef struct {
	q_value_t value;
	_u8_t _data;
} q_u8_t;

typedef struct {
	q_value_t value;
	_u16_t _data;
} q_u16_t;

typedef struct {
	q_value_t value;
	_u32_t _data;
} q_u32_t;

typedef struct {
	q_value_t value;
	_u64_t _data;
} q_u64_t;

/* >>> floating-point <<< */

typedef struct {
	q_value_t value;
	_float_t _data;
} q_float_t;

typedef struct {
	q_value_t value;
	_double_t _data;
} q_double_t;

/* >>> string (utf8) <<< */

typedef struct {
	q_value_t value;
	_string_t _data;
} q_string_t;

/* >>> ptr <<< */

typedef struct {
	q_value_t value;
	_ptr_t _data;
} q_ptr_t;

/* >>> thread <<< */

typedef struct {
	q_value_t value;
	_ptr_t _data;
} q_thread_t;

void q_value_dump(q_value_t *val);
void q_value_print(q_value_t *val);

#endif
