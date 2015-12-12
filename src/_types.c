#include <stdlib.h>
#include <stdio.h>

#include "_types.h"

// TODO q_value_to_string
void q_value_dump(q_value_t *val) {
	if (!val) {
		fprintf(stderr, "*** q_value_dump: %p\n", val);
		return;
	}
	
	switch(val->type) {
		case S8:
			printf("q_value_t [S8: %d]\n", ((q_s8_t  *)val)->_data);
			break;
		case S16:
			printf("q_value_t [S16: %d]\n", ((q_s16_t *)val)->_data);
			break;
		case S32:
			printf("q_value_t [S32: %d]\n", ((q_s16_t *)val)->_data);
			break;
		case FLOAT:
			printf("q_value_t [FLOAT: %g]\n", ((q_float_t *)val)->_data);
			break;
		case DOUBLE:
			printf("q_value_t [DOUBLE: %g]\n", ((q_double_t *)val)->_data);
			break;
		case STRING:
			printf("q_value_t [STRING: \"%s\"]\n", ((q_string_t *)val)->_data);
			break;
		case PTR:
			printf("q_value_t [PTR: %p]\n", ((q_ptr_t *)val)->_data);
			break;
		default:
			fprintf(stderr, "q_value_t [???]\n");
	}
}

void q_value_print(q_value_t *val) {
	if (!val) {
		fprintf(stderr, "*** q_value_print: %p\n", val);
		return;
	}
	
	switch(val->type) {
		case S8:
			printf("%d", ((q_s8_t  *)val)->_data);
			break;
		case S16:
			printf("%d", ((q_s16_t *)val)->_data);
			break;
		case S32:
			printf("%d", ((q_s16_t *)val)->_data);
			break;
		case FLOAT:
			printf("%g", ((q_float_t *)val)->_data);
			break;
		case DOUBLE:
			printf("%g", ((q_double_t *)val)->_data);
			break;
		case STRING:
			printf("%s", ((q_string_t *)val)->_data);
			break;
		case PTR:
			printf("%p", ((q_ptr_t *)val)->_data);
			break;
		default:
			fprintf(stderr, "q_value_t [???]\n");
	}
}

