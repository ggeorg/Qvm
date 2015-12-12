	call	do_something

	dump
	ret

:do_something
	joe	on_error
		s32	32
		s32	0
		div
	clr

	jmp	finally

:on_error			; Error Handler
	pop				; ignore the error code

	s32	32
	s32	2
	div

:finally

	ret
