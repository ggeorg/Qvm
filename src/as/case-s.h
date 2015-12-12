{
	char *p;
	
	switch(*line_ptr++) {
		case '8': {
				_s32_t val;
				p = line_ptr;
				if (is_eol(p)) { /* s8 */
					q_ops_push(ctx, q_op_cnvto_s8());
				} else if (is_skip(p[0])) { /* s8 <number> */
					line_ptr++; skip();
					val = read_long();
					q_ops_push(ctx, q_op_push_s8((_s8_t)val));
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case '1': {
				_s32_t val;
				p = line_ptr;
				
				if (p[0] == '6') {
					if (is_eol(p)) { /* s16 */
						q_ops_push(ctx, q_op_cnvto_s16());
					} else if(is_skip(p[1])) { /* s16 <number> */
						line_ptr++; skip();
						val = read_long();
						q_ops_push(ctx, q_op_push_s16((_s16_t)val));
					} else {
						err_invalid_op();
					}
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case '3':{
				_s32_t val;
				p = line_ptr;
				if (p[0] == '2') {
					if (is_eol(p)) { /* s32 */
						q_ops_push(ctx, q_op_cnvto_s32());
					} else if(is_skip(p[1])) { /* s32 <number> */
						line_ptr++; skip();
						val = read_long();
						q_ops_push(ctx, q_op_push_s32(val));
					} else {
						err_invalid_op();
					}
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case '6':{
				_s64_t val;
				p = line_ptr;
				if (p[0] == '4' && is_skip(p[1])) {
					if (is_eol(p)) { /* s64 */
						q_ops_push(ctx, q_op_cnvto_s64());
					} else if(is_skip(p[1])) { /* s64 <number> */
						line_ptr++; skip();
						val = read_llong();
						q_ops_push(ctx, q_op_push_s64(val));
					} else {
						err_invalid_op();
					}
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case 't':{
				char *val;
				p = line_ptr;
				if (p[0] == 'r' && is_skip(p[1])) { /* str <string> */
					line_ptr += 2; skip();
					val = read_string();
					q_ops_push(ctx, q_op_push_string(val));
				} else {
					err_invalid_op();
				}
			}
			break;
			
		default:
			err_invalid_op();
			break;
	}
}

