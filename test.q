
	s32	200
	pop	[lala]
	
	call	main1
	str	"<<< main1"
	dump
	
	ret
	
:main1
	call	main2
	str	"<<< main2"
	
	ret
	
:main2
	push	[lala]
	s32	0
	
	dump
	
	joe	error
		div
	clr
	
	jmp	finally
	
:error
	dump
	
	str	"Error Handler"

:finally
	str	"FINALLY"
	
	push	[lll]
	
	ret

