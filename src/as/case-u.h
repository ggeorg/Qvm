{
	char *p;
	
	switch(*line_ptr++) {
		case '8': {
				_u32_t val;
				p = line_ptr;
				if (is_eol(p)) { /* u8 */
					q_ops_push(ctx, q_op_cnvto_u8());
				} else if (is_skip(p[0])) { /* u8 <number> */
					line_ptr++; skip();
					val = read_ulong();
					q_ops_push(ctx, q_op_push_u8((_u8_t)val));
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case '1': {
				_u32_t val;
				p = line_ptr;
				
				if (p[0] == '6') {
					if (is_eol(p)) { /* u16 */
						q_ops_push(ctx, q_op_cnvto_u16());
					} else if(is_skip(p[1])) { /* u16 <number> */
						line_ptr++; skip();
						val = read_ulong();
						q_ops_push(ctx, q_op_push_u16((_u16_t)val));
					} else {
						err_invalid_op();
					}
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case '3':{
				_u32_t val;
				p = line_ptr;
				if (p[0] == '2') {
					if (is_eol(p)) { /* u32 */
						q_ops_push(ctx, q_op_cnvto_u32());
					} else if(is_skip(p[1])) { /* u32 <number> */
						line_ptr++; skip();
						val = read_ulong();
						q_ops_push(ctx, q_op_push_u32(val));
					} else {
						err_invalid_op();
					}
				} else {
					err_invalid_op();
				}
			}
			break;
			
		case '6':{
				_u64_t val;
				p = line_ptr;
				if (p[0] == '4' && is_skip(p[1])) {
					if (is_eol(p)) { /* u64 */
						q_ops_push(ctx, q_op_cnvto_u64());
					} else if(is_skip(p[1])) { /* u64 <number> */
						line_ptr++; skip();
						val = read_ullong();
						q_ops_push(ctx, q_op_push_u64(val));
					} else {
						err_invalid_op();
					}
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

