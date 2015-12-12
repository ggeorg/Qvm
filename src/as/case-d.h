{
	char *p;
	
	switch(*line_ptr++) {
		case 'b': {	
				_double_t val;
				p = line_ptr;
				if (p[0] == 'l' && is_skip(p[1])) { /* dbl <number> */
					line_ptr += 2; skip();
					val = read_double();
					q_ops_push(ctx, q_op_push_double(val));
				} else {
					err_invalid_op();
				}
				
			}
			break;
		
		case 'i':
			p = line_ptr;
			if (p[0] == 'v' && is_eol(&p[1])) { /* div */
				q_ops_push(ctx, q_op_div());
			} else {
				err_invalid_op();
			}
			break;
			
		case 'u':
			p = line_ptr;
			if (p[0] == 'm' && p[1] == 'p' && is_eol(&p[2])) { /* dump */
				q_ops_push(ctx, q_op_dump());
			} else {
				err_invalid_op();
			}
			break;
			
		default:
			err_invalid_op();
			break;
	}
	
}
