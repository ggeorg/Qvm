	call	do_something

	dump
	ret

:do_something
	throw	-9999	; throw exception with error code = -9999

	ret
