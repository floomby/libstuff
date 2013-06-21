; I abhorror gas so I am using nasm for now
; this is 64 bits so pointers are 8 bytes

[BITS 64]

tramp:
	push QWORD [rsp]
	mov QWORD [rsp+8], 12345678h
	; since we cannot do a "far call" we use this trick
	push 01234567h
	ret