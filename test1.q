.dlopen Math

:lala
	dbl	0				; result
	dbl	625			; argument(s)
	s8		1				; argc
	inv	Math:sqrt
	
	dbl	0
	dbl   2	
	rot	2  			; previous result 
	s8		2
	inv	Math:pow

	s8		1

	dump
	
	str	"Hello, World!"
	
	dump

	pop	3	
	ret
	
; --->
