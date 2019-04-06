0000           : alloc 1 v$a		; $a
0001 >   fmain : fbegin
0002           : v$a = 123
0003           : fend
%include	'io.asm'

section	.bss
sinput:	resb	255	;reserve a 255 byte space in memory for the users input string
v$a:	resd	1

section	.text
global _start
_start:
	call	fmain
	mov	eax, 1
	int	0x80
fmain:
	push	ebp
	mov	ebp, esp
	mov	dword [ebp - 4], 123
	pop	ebp
	ret
