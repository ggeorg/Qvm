#include <stdlib.h>
#include <stdio.h>

#include "Qvm.h"
#include "qvm-gc.h"
#include "as/Qas.h"

#include "operations.h"

int xmain(int argc, char **argv) {
	q_context_t ctx;
	
	q_ctx_init(&ctx, 255, 255);

	q_ops_push(&ctx, q_op_push_s8(1));
	q_ops_push(&ctx, q_op_call("fcn1"));
	
	q_ops_push(&ctx, q_op_dump());
	q_ops_push(&ctx, q_op_pop());
	q_ops_push(&ctx, q_op_dump());
	
	q_ops_push(&ctx, q_op_ret());

	q_ops_label(&ctx, "fcn1");
	q_ops_push(&ctx, q_op_rot(1));
	q_ops_push(&ctx, q_op_dump());
	
	q_ops_push(&ctx, q_op_push_string("in fcn1"));
	q_ops_push(&ctx, q_op_dump());
	q_ops_push(&ctx, q_op_rot(2));
	q_ops_push(&ctx, q_op_dump());
	
	q_ops_push(&ctx, q_op_pop());
	q_ops_push(&ctx, q_op_ret());
	
	q_exec(&ctx, NULL);
	//q_dump(&ctx);
}

int main(int argc, char **argv) {
	q_context_t ctx;
	
	FILE *fp;
	
	q_gc_init();
	
	if (argc != 2) {
		fprintf(stderr, "no input file\n");
		return -1;
	}
	
	fp = fopen(argv[1], "r");
	if (!fp) {
		fprintf(stderr, "can't open file `%s'\n", argv[1]);
		return -1;
	}
	
	q_ctx_init(&ctx, 255, 255);
	
	if (parse_file(&ctx, fp)) {
		q_exec(&ctx, NULL);
		//q_dump(&ctx);
	}

	return 0;
}
