#ifndef __QASM_H__
#define __QASM_H__

#include <stdio.h>

#include "Qas.h"
#include "../Qvm.h"

#define MAX_LINE_LEN    256	/* 64KB line */

#define EXIT_CODE_INVALID_OPERATION			-1
#define EXIT_CODE_INVALID_IDENTIFIER		-2
#define EXIT_CODE_INVALID_FLOAT				-3

int parse_file(q_context_t *ctx, FILE *fp);

#endif
