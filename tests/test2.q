	s32	512
	flt	512.1

	jne	lala
	
	jmp	exit
	
:lala

	add

:exit

	s32 	1
	s32	255
	s8		2
	new			; this creates a structure
	
	fld	0
	
	if
	pop

	dump
