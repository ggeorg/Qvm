	
	run	thread1
	
	s32	100
	dump

:endless
	jmp	endless
	
:thread1
	s32	100
	
:loop
	jz		dec
	jmp	exit

:dec
	s32	1
	sub
	dump
	jmp	loop
	
:exit
