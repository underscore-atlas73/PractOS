.global displayString
.type displayString, @function
.section .text
displayString:
displayString_loop:
	mov %esi, %
	lodsb

	

	orb %al, %al
	jnz displayString_loop
	ret