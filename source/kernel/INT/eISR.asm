.extern e_interrupt_service_routine

# Macro for exceptions that DO NOT push an error code
.macro eISR_NOERRCODE num
.global eISR\num
eISR\num:
	cli
	pushq $0		  # Push dummy error code
	pushq $\num	   	  # Push the interrupt number
	jmp eISR_common_stub
.endm

# Macro for exceptions that DO push an error code
.macro eISR_ERRCODE num
.global eISR\num
eISR\num:
	cli
	pushq $\num	   	  # Push the interrupt number
	jmp eISR_common_stub
.endm

# --- Standard Exceptions ---
eISR_NOERRCODE 0  # Divide by zero
eISR_NOERRCODE 1  # Debug
eISR_NOERRCODE 2  # Non-maskable interrupt
eISR_NOERRCODE 3  # Breakpoint
eISR_NOERRCODE 4  # Overflow
eISR_NOERRCODE 5  # Bound range exceeded
eISR_NOERRCODE 6  # Invalid opcode
eISR_NOERRCODE 7  # Device not available

# --- Exceptions with Error Codes ---
eISR_ERRCODE   8  # Double fault
eISR_NOERRCODE 9  # Coprocessor segment overrun (legacy)
eISR_ERRCODE   10 # Invalid TSS
eISR_ERRCODE   11 # Segment not present
eISR_ERRCODE   12 # Stack-segment fault
eISR_ERRCODE   13 # General protection fault
eISR_ERRCODE   14 # Page fault

eISR_NOERRCODE 15 # Reserved
eISR_NOERRCODE 16 # x87 floating-point exception
eISR_ERRCODE   17 # Alignment check
eISR_NOERRCODE 18 # Machine check
eISR_NOERRCODE 19 # SIMD floating-point exception
eISR_NOERRCODE 20 # Virtualization exception
eISR_ERRCODE   21 # Control Protection Exception
eISR_NOERRCODE 22 # Reserved
eISR_NOERRCODE 23 # Reserved
eISR_NOERRCODE 24 # Reserved
eISR_NOERRCODE 25 # Reserved
eISR_NOERRCODE 26 # Reserved
eISR_NOERRCODE 27 # Reserved
eISR_NOERRCODE 28 # Hypervisor Injection Exception
eISR_ERRCODE   29 # VMM Communication Exception
eISR_ERRCODE   30 # Security Exception
eISR_NOERRCODE 31 # Reserved

eISR_common_stub:
	# 1. Save all general-purpose registers (Relavent to SysV ABI)
	pushq %rax
	pushq %rbx
	pushq %rcx
	pushq %rdx
	pushq %rbp
	pushq %rsi
	pushq %rdi
	pushq %r8
	pushq %r9
	pushq %r10
	pushq %r11
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15

	# 2. Call the C handler
	# Pass the current stack pointer (%rsp) as the first argument (%rdi)
	movq %rsp, %rdi
	call e_interrupt_service_routine

	# 3. Restore all general-purpose registers
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %r11
	popq %r10
	popq %r9
	popq %r8
	popq %rdi
	popq %rsi
	popq %rbp
	popq %rdx
	popq %rcx
	popq %rbx
	popq %rax

	# 4. Clean up the error code and interrupt number (2 * 8 bytes = 16)
	addq $16, %rsp

	# 5. Return from interrupt
	sti
	iretq