#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Qas.h"
#include "../operations.h"
#include "../qvm-gc.h"

static FILE *input;		/* current source file */
static q_context_t *ctx;

static int lineno;	/* line number baing parsed */

/* input line */
char line[MAX_LINE_LEN];
char *line_ptr;			/* pointer to next char on line */

/* static functions */
static void parse();

/* errors */

static void err_invalid_op() {
	fprintf(stderr, "*** invalid operation at col: %ld, line: %d\n", 
		(line_ptr - line), lineno);
	exit(EXIT_CODE_INVALID_OPERATION);
}

static void err_invalid_ident() {
	fprintf(stderr, "*** invalid identifier at col: %ld, line: %d\n", 
		(line_ptr - line), lineno);
	exit(EXIT_CODE_INVALID_IDENTIFIER);
}

static void err_invalid_float() {
	fprintf(stderr, "*** invalid float at col: %ld, line: %d\n", 
		(line_ptr - line), lineno);
	exit(EXIT_CODE_INVALID_FLOAT);
}

static void err_invalid_double() {
	fprintf(stderr, "*** invalid double at col: %ld, line: %d\n", 
		(line_ptr - line), lineno);
	exit(EXIT_CODE_INVALID_FLOAT);
}

/* warnings */
static void warn_invalid_ident() {
	fprintf(stderr, "!!! invalid identifier at col: %ld, line: %d\n", 
			(line_ptr - &line[0]), lineno);
}

/* Determines if a character is alphabetic or underscore. 
 * These can be used for first or subsequent chars in an 
 * identifier. 
 */
static int is_ident(char c) {
	return (isalpha(c) || (c == '_'));
}

/* Determines if character is "skip" character. All values
 * from 0x20 down to CTRL-A are skipped.
 */
static int is_skip(char c) {
	return ((c > 0) && (c <= ' '));
}

/* Is End-Of-Line reached? */
static int is_eol(char *p) {
	while(is_skip(*p))
		++p;
	
	if (!(*p)) /* end of line */
		return 1;
		
	if (*p == ';') { /* if commet */
		return 1; 
	}
	
	return 0;
}

/* Skip whitespace. */
static void skip() {
	while(is_skip(*line_ptr))
		++line_ptr;
}

static char *read_ident() {
	char *label, *p = line_ptr;
	int len;
	
	len = 0;
	if (is_ident(*p)) {
		++len;
		++p;
	}
	
	while(isalnum(*p) || (*p == '_') || (*p == '.')) {
		++len;
		++p;
	}
	
	if (len > 0) {
		label = (char *)q_gc_malloc(len + 1);
		strncpy(label, line_ptr, len);
		label[len] = '\0';
		line_ptr += len;
		return label;
	} else {
		// TODO error
		return NULL;
	}
}

static char *read_varname() {
	char *name;
	
	if (*line_ptr == '[') {
		++line_ptr;
		name = read_ident();
		skip();
		if (*line_ptr++ == ']')
			return name;
	}
	
	return NULL;
}

static char *read_string() {
	char *result, *p = ++line_ptr; // skip double quote
	char buf[MAX_LINE_LEN], *bp = buf;
	int len;

	len = 0;
	while(*p != '"') {
		if (len++ == MAX_LINE_LEN - 1) {
			fprintf(stderr, "not a valid string\n");
			exit(1);
		}
		
		if (*p == '\\') {
			++p;

			if (*p == 'n') {
				*bp++ = '\n';
			} else if (*p == 'r') {
				*bp++ = '\r';
			} else if (*p == 't') {
				*bp++ = '\t';
			} else if (*p == '"' || *p == '\\') {
				*bp++ = *p++;
			} else {
				fprintf(stderr, "not a valid string\n");
				exit(1);
			}
		} else {
			*bp++ = *p++;
		}
	}
	*bp = '\0';
	
	len = strlen(buf);
	result = (char *)q_gc_malloc(len + 1);
	strncpy(result, buf, len);
	line_ptr = p;

	return result;
}

static int read_optype() {
	if(*line_ptr == '8' &&  is_skip(*(line_ptr + 1))) {
		line_ptr += 2;
		return 8;
	} else if (*line_ptr == '1' && *(line_ptr + 1) == '6' &&  is_skip(*(line_ptr + 2))) {
		line_ptr += 3;
		return 16;
	} else if (*line_ptr == '3' && *(line_ptr + 1) == '2' &&  is_skip(*(line_ptr + 2))) {
		line_ptr += 3;
		return 32;
	} else if (*line_ptr == '6' && *(line_ptr + 1) == '4' &&  is_skip(*(line_ptr + 2))) {
		line_ptr += 3;
		return 64;
	} 
	return -1;
}

static int read_numbase() {
	if (*line_ptr == '0' && *(line_ptr + 1) == 'x') {
		line_ptr += 2;
		return 16;
	} else {
		return 10;
	}
}

static _s64_t read_llong(int *error) {
	char *endptr;
	int base;
	
	_s64_t val = 0;
	
	base = read_numbase();
	val = strtoll(line_ptr, &endptr, base);
	if (!is_eol(endptr)) {
		*error = 1;
	}
	
	return val;
}

static _u64_t read_ullong(int *error) {
	char *endptr;
	int base;
	
	_u64_t val = 0;
	
	base = read_numbase();
	val = strtoull(line_ptr, &endptr, base);
	if (!is_eol(endptr)) {
		*error = 1;
	}
	
	return val;
}

static _s32_t read_long(int *error) {
	char *endptr;
	int base;
	
	_s32_t val = 0;
	
	base = read_numbase();
	val = strtol(line_ptr, &endptr, base);
	if (!is_eol(endptr)) {
		*error = 1;
	}
	
	return val;
}

static _u32_t read_ulong(int *error) {
	char *endptr;
	int base;
	
	_u32_t val = 0;
	
	base = read_numbase();
	val = strtoul(line_ptr, &endptr, base);
	if (!is_eol(endptr)) {
		*error = 1;
	}
	
	return val;
}

static _float_t read_float(int *error) {
	char *endptr;
	
	_float_t val = strtof(line_ptr, &endptr);
	if (!is_eol(endptr)) {
		*error = 1;
	}
	
	return val;
}

static _double_t read_double(int *error) {
	char *endptr;
	
	_double_t val = strtod(line_ptr, &endptr);
	if (!is_eol(endptr)) {
		*error = 1;
	}
	
	return val;
}

static void do_sN(int optype) {
	int error = 0;
	
	skip();
	
	if (*line_ptr == '[') {
		++line_ptr;
		
		// identifier
		
	} else if (optype == 64) {
		if (is_eol(line_ptr)) {
			q_ops_push(ctx, q_op_cnvto_s64());
		} else {
			_s64_t val = read_llong(&error);
			if (error) {
				// TODO error
				return;
			}
			q_ops_push(ctx, q_op_push_s64((_s64_t)val));
		}
	} else {
		if (is_eol(line_ptr)) {
			switch (optype) {
				case 8:
					q_ops_push(ctx, q_op_cnvto_s8());
					break;
				case 16:
					q_ops_push(ctx, q_op_cnvto_s16());
					break;
				case 32:
					q_ops_push(ctx, q_op_cnvto_s32());
					break;
			}
		} else {
			_s32_t val = read_long(&error);
			if (error) {
				// TODO error
				return;
			}

			switch (optype) {
			case 8:
				q_ops_push(ctx, q_op_push_s8((_s8_t)val));
				break;
			case 16:
				q_ops_push(ctx, q_op_push_s16((_s16_t)val));
				break;
			case 32:
				q_ops_push(ctx, q_op_push_s32((_s32_t)val));
				break;
			}
		}
	}
}

static void do_uN(int optype) {
	int error = 0;
	
	while(is_skip(*line_ptr))
		++line_ptr;
	
	if (*line_ptr == '[') {
		++line_ptr;
		
		// identifier
	
	} else if (optype == 64) {
		if (is_eol(line_ptr)) {
			q_ops_push(ctx, q_op_cnvto_u64());
		} else {
			_u64_t val = read_ullong(&error);
			if (error) {
				// TODO error
				return;
			}
			q_ops_push(ctx, q_op_push_u64((_u64_t)val));
		}
	} else {
		if (is_eol(line_ptr)) {
			switch (optype) {
				case 8:
					q_ops_push(ctx, q_op_cnvto_u8());
					break;
				case 16:
					q_ops_push(ctx, q_op_cnvto_u16());
					break;
				case 32:
					q_ops_push(ctx, q_op_cnvto_u32());
					break;
			}
		} else {
			_u32_t val = read_ulong(&error);
			if (error) {
				// TODO error
				return;
			}

			switch (optype) {
			case 8:
				q_ops_push(ctx, q_op_push_u8((_u8_t)val));
				break;
			case 16:
				q_ops_push(ctx, q_op_push_u16((_u16_t)val));
				break;
			case 32:
				q_ops_push(ctx, q_op_push_u32((_u32_t)val));
				break;
			}
		}
	}
}

static void do_dlopen() {
	switch(*line_ptr++) {
		case 'd': {
				char *module, *p = line_ptr;
				
				if (p[0] == 'l' && p[1] == 'o' && p[2] == 'p' && p[3] == 'e' 
						&& p[4] == 'n' && is_skip(p[5])) {
					line_ptr += 6; skip();
					module = read_ident();
					if (module && is_eol(line_ptr)) {
						q_dlopen(ctx, module);
					} else {
						err_invalid_ident();
					}
				}
			}
			break;
			
		default:
			// TODO warning
			break;
	}
}

static void do_label() {
	char *label;
	
	label = read_ident();
	
	if (label) {
		/* Qvm Op */
		q_ops_label(ctx, label);

		/* continue with same line */
		parse();
	} else {
		warn_invalid_ident();
	}
}

static void do_operation() {
	switch(*line_ptr++) {
		case 'a': {
				char *p = line_ptr;
				if (p[0] == 'd' && p[1] == 'd' && is_eol(&p[2])) {
					q_ops_push(ctx, q_op_add());
				}
			}
			break;
			
		case 'c': {
				char *label, *p = line_ptr;
				if (p[0] == 'a' && p[1] == 'l' && p[2] == 'l' && is_skip(p[3])) {
					line_ptr += 4; skip();
					label = read_ident();
					if (label && is_eol(line_ptr)) {
						q_ops_push(ctx, q_op_call(label));
					} else {
						err_invalid_ident();
					}
				} else
				/* clr */
				if (p[0] == 'l' && p[1] == 'r' && is_eol(&p[2])) {
					q_ops_push(ctx, q_op_clr());
				}
			}
			break;
			
		case 'd': 
			#include "case-d.h"
			break;
			
		case 'f': {
				char *p = line_ptr;
				_float_t val;
				int error = 0;
	
				if (p[0] == 'l' && p[1] == 't' && is_skip(p[2])) {
					line_ptr += 3; skip();
					val = read_float(&error);
					if (error) {
						err_invalid_float();
					}
					q_ops_push(ctx, q_op_push_float((_float_t)val));
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case 'i': {
				char *mod, *sym, *p = line_ptr;
				
				if (p[0] == 'n' && p[1] == 'v') {
					if (is_skip(p[2])) {
						line_ptr += 3; skip();
						mod = read_ident();
						if (mod && (*line_ptr++ == ':')) {
							sym = read_ident();
							if (sym && is_eol(line_ptr)) {
								q_ops_push(ctx, q_op_invoke(mod, sym));
							} else {
								err_invalid_ident();
							}
						} else {
							err_invalid_ident();
						}
					} else if (p[2] == 'v' && is_skip(p[3])) {
						line_ptr += 4; skip();
						mod = read_ident();
						if (mod && (*line_ptr++ == ':')) {
							sym = read_ident();
							if (sym && is_eol(line_ptr)) {
								q_ops_push(ctx, q_op_invoke_void(mod, sym));
							} else {
								err_invalid_ident();
							}
						} else {
							err_invalid_ident();
						}
					}
				}
			}
			break;
			
		case 'j':
			#include "case-j.h"
			break;
			
		case 'm': {
				char *p = line_ptr;
				if (p[0] == 'u' && p[1] == 'l' && is_eol(&p[2])) {
					q_ops_push(ctx, q_op_mul());
				}
			}
			break;
			
		case 'p': {
				char *name, *p = line_ptr;
				
				if (p[0] == 'o' && p[1] == 'p' && is_skip(p[2])) {
					if (is_eol(&p[2])) {
						q_ops_push(ctx, q_op_pop());
					} else {
						int error = 0;
						_s8_t val;
				
						line_ptr += 3; skip();
						if (*line_ptr == '[') {
							name = read_varname();
							if (name && is_eol(line_ptr)) {
								q_ops_push(ctx, q_op_pop_v(name));
							} else {
								err_invalid_ident();
							}
						} else {
							val = (_s8_t)read_long(&error);
							if (error) {
								// TODO error
								return;
							}
							q_ops_push(ctx, q_op_pop_n(val));
						}
					}
				} else if (p[0] == 'r' && p[1] == 'i' && p[2] == 'n' 
						&& p[3] == 't' && is_eol(&p[4])) {
					q_ops_push(ctx, q_op_print());
				} else if (p[0] == 'u' && p[1] == 's' && p[2] == 'h' 
						&& is_skip(p[3])) {
					line_ptr += 4; skip();
					name = read_varname();
					if (name && is_eol(line_ptr)) {
						q_ops_push(ctx, q_op_push(name));
					} else {
						err_invalid_ident();
					}
				}
			}
			break;
			
		case 'r': {
				char *label, *p = line_ptr;
				if (p[0] == 'e' && p[1] == 't' && is_eol(&p[2])) {
					q_ops_push(ctx, q_op_ret());
				} else if (p[0] == 'o' && p[1] == 't' && is_skip(p[2])) {
					if (is_eol(&p[2])) {
						q_ops_push(ctx, q_op_rot());
					} else {
						int error = 0;
						_s8_t val;
				
						line_ptr += 3; skip();
						val = (_s8_t)read_long(&error);
						if (error) {
							// TODO error
							return;
						}
						q_ops_push(ctx, q_op_rot_n(val));
					}
				} else if (p[0] == 'u' && p[1] == 'n' && is_skip(p[2])) {
					line_ptr += 3; skip();
					label = read_ident();
					if (label && is_eol(line_ptr)) {
						q_ops_push(ctx, q_op_run(label));
					} else {
						err_invalid_ident();
					}
				}
			}
			break;
			
		case 's': {
				int optype = read_optype();
				if (optype != -1) {
					do_sN(optype);
				} else {
					char *p = line_ptr;
					if (p[0] == 'u' && p[1] == 'b' && is_eol(&p[2])) {
						q_ops_push(ctx, q_op_sub());
					} else if (p[0] == 't' && p[1] == 'r' && is_skip(p[2])) {
						char *val;
						
						line_ptr += 3; skip();
						if (*line_ptr == '"') {
							 // read string will exit on error
							val = read_string();
							q_ops_push(ctx, q_op_push_string(val));
						} else {
							// TODO ???
							return;
						}
					}
				}
			}
			break;
			
		case 'u': {
				int optype = read_optype();
				if (optype != -1) {
					do_uN(optype);
				}
			}
			break;
	}
}

static void parse() {
	int i;

	/* skip whitespace */
	skip();
	
	/* end of line? */
	if (is_eol(line_ptr))
		return;
		
	/* dlopen ? */
	if (*line_ptr == '.') {
		++line_ptr;
		do_dlopen();
		return;
	}
	
	/* label ? */
	if (*line_ptr == ':') {
		++line_ptr;
		do_label();
		return;
	}
	
	/* See if it's a legal char for identifier or reserved word. */
	/* If so, pick it up and put it in the TString ALL UPPER CASE */
	
	i = 0;
	if (is_ident(*line_ptr)) {
		do_operation();
		return;
	}
}

static int readline(void) {
	/* Reads in at most one less than size characters. Reading
	 * stops after an EOF or a newline. If a newline is read, 
	 * it is stired into the buffer. A terminating '\0' is stored
	 * after the last character in the buffer.
	 */
	if (!fgets(line_ptr = line, MAX_LINE_LEN, input)) {
		fclose(input);
		return 0;
	}
	
	return ++lineno;
}

int parse_file(q_context_t *_ctx, FILE *fp) {
	ctx = _ctx;
	input = fp;

	while(1) {
		if (readline()) {
			parse();
		} else {
			return 1;
		}
	}
}
