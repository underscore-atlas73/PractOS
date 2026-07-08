.global detectCPUID
.type detectCPUID, @function
.text
detectCPUID:
	pushfl				#Save original EFLAGS
	pushfl				#Temp store EFLAGS
	xorl $0x00200000, (%esp) 	#attempt to flip CPUID bit
	popfl 				#Load (potentially) modified EFLAGS
	pushfl 				#push EFLAGS to
	pop %eax 			#store EFLAGS in EAX (may be modified)
	xor (%esp), %eax 		#eax bits are 1 if changed
	popfl 				#Restore original EFLAGS
	and $0x00200000, %eax		#EAX will be zero if no change to CPUID bit, nonzero else
	ret

.global displayVendorIDStringRegisters
.type displayVendorIDStringRegister, @function
displayVendorIDStringRegister:
	pushl %ecx
	pushl %edx
	pushl %ebx

	mov $6, %ecx
	mov $0xB8000, %edi
displayVendorIDStringRegister_loop:
	popw %ax

	movb %al, (%edi)
	inc %edi
	movb $0x07, (%edi)
	inc %edi

	movb %ah, (%edi)
	inc %edi
	movb $0x07, (%edi)
	inc %edi

	dec %ecx
	jnz displayVendorIDStringRegister_loop

	ret