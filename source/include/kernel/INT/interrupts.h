#ifndef INT_H
#define INT_H

#include <stdint.h>

struct InterruptState{
	// Registers pushed by stub stage1
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
	uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;

	// Pushed by stage0
	uint64_t int_no;
	uint64_t err_code;

	// Automatically pushed by the CPU
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
} __attribute__((packed));

extern void PIT_handler(struct InterruptState*);
extern void KB_handler(struct InterruptState*);

#endif
