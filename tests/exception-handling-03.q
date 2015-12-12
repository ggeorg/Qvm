	call	do_something

	dump
	ret

:do_something
	joe	on_error
		joe	on_error_2
			s32	32
			s32	0
			div
		clr
	clr

	jmp	finally

:on_error			; Error Handler
	pop				; ignore the error code

	s32	32
	s32	2
	div

	jmp	finally

:on_error_2			; Error Handler #2
	pop				; ignore the error code

	s32	64
	s32	8
	div

:finally

	ret	
