.extern ISR_common_stub

# Macro for IRQ
.macro IRQ num
.global IRQ\num
IRQ\num:
	cli
	pushq $0		  # Push dummy error code
	pushq $(\num+32) 	  # Push the interrupt number
	jmp ISR_common_stub
.endm

##################################
IRQ 0	# PIT
IRQ 1	# KB
##################################
