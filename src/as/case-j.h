{				
	char *label, *p;
	
	switch(*line_ptr++) {
		case 'e': /* jeq <label> */
			p = line_ptr;
			if (p[0] == 'q' && is_skip(p[1])) {
				line_ptr += 2; skip();
				label = read_ident();
				if (label && is_eol(line_ptr)) {
					q_ops_push(ctx, q_op_jeq(label));
				} else {
					err_invalid_ident();
				}
			}
			break;
			
		case 'g':
			switch(*line_ptr++) {
				case 'e': /* jge <label> */
					if (is_skip(*line_ptr)) {
						++line_ptr; skip();
						label = read_ident();
						if (label && is_eol(line_ptr)) {
							q_ops_push(ctx, q_op_jge(label));
						} else {
							err_invalid_ident();
						}
					}
					break;
					
				case 't': /* jgt <label> */
					if (is_skip(*line_ptr)) {
						++line_ptr; skip();
						label = read_ident();
						if (label && is_eol(line_ptr)) {
							q_ops_push(ctx, q_op_jgt(label));
						} else {
							err_invalid_ident();
						}
					}
					break;
			}
			break;
			
		case 'l':
			switch(*line_ptr++) {
				case 'e': /* jle <label> */
					if (is_skip(*line_ptr)) {
						++line_ptr; skip();
						label = read_ident();
						if (label && is_eol(line_ptr)) {
							q_ops_push(ctx, q_op_jle(label));
						} else {
							err_invalid_ident();
						}
					}
					break;
					
				case 't': /* jlt <label> */
					if (is_skip(*line_ptr)) {
						++line_ptr; skip();
						label = read_ident();
						if (label && is_eol(line_ptr)) {
							q_ops_push(ctx, q_op_jlt(label));
						} else {
							err_invalid_ident();
						}
					}
					break;
			}
			break;
			
		case 'm': /* jmp <label> */
			p = line_ptr;
			if (p[0] == 'p' && is_skip(p[1])) {
				line_ptr += 2; skip();
				label = read_ident();
				if (label && is_eol(line_ptr)) {
					q_ops_push(ctx, q_op_jmp(label));
				} else {
					err_invalid_ident();
				}
			}
			break;
			
		case 'n':
			switch(*line_ptr++) {
				case 'e': /* jne <label> */
					if (is_skip(*line_ptr)) {
						++line_ptr; skip();
						label = read_ident();
						if (label && is_eol(line_ptr)) {
							q_ops_push(ctx, q_op_jne(label));
						} else {
							err_invalid_ident();
						}
					}
					break;
					
				case 'z': /* jnz <label> */
					if (is_skip(*line_ptr)) {
						++line_ptr; skip();
						label = read_ident();
						if (label && is_eol(line_ptr)) {
							q_ops_push(ctx, q_op_jnz(label));
						} else {
							err_invalid_ident();
						}
					} else {
						err_invalid_op();
					}
					break;
					
				default:
					err_invalid_op();
					break;
			}
			break;
			
		case 'o': /* joe <label> */
			p = line_ptr;
			if (p[0] == 'e' && is_skip(p[1])) {
				line_ptr += 2; skip();
				label = read_ident();
				if (label && is_eol(line_ptr)) {
					q_ops_push(ctx, q_op_joe(label));
				} else {
					err_invalid_ident();
				}
			} else {
				err_invalid_op();
			}
			break;
			
		case 'z': /* jz <label> */
			if (is_skip(*line_ptr)) {
				++line_ptr; skip();
				label = read_ident();
				if (label && is_eol(line_ptr)) {
					q_ops_push(ctx, q_op_jz(label));
				} else {
					err_invalid_ident();
				}
			} else {
				err_invalid_op();
			}
			break;
			
		default:
			err_invalid_op();
			break;
	}
}

