; I abhorror gas so I am using nasm for now
; this is 64 bits so pointers are 8 bytes

[BITS 64]

; the constants may seem a bit weird, they are 
; just for seeing there location in the ouput
; the real function replacece the consts with
; the address that should be there

tramp:
	push QWORD [rsp]
	mov QWORD [rsp+8], 12345678h
	; since we cannot do a "far call" we use this trick
	push 01234567h
	ret
