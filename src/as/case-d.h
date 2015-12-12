{
	char *p;
	
	switch(*line_ptr++) {
		case 'b': {	/* dbl <number> */
				_double_t val;
				int error = 0;	
				p = line_ptr;
				if (p[0] == 'l' && is_skip(p[1])) {
					line_ptr += 2; skip();
					val = read_double(&error);
					if (error) {
						err_invalid_double();
					}
					q_ops_push(ctx, q_op_push_double((_double_t)val));
				} else {
					err_invalid_op();
				}
				
			}
			break;
		
		case 'i': /* div */
			p = line_ptr;
			if (p[0] == 'v' && is_eol(&p[1])) {
				q_ops_push(ctx, q_op_div());
			} else {
				err_invalid_op();
			}
			break;
			
		case 'u': /* dump */
			p = line_ptr;
			if (p[0] == 'm' && p[1] == 'p' && is_eol(&p[2])) {
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
