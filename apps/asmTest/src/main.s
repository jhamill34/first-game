.global _myadd 
.align 4


/*
	The stack here looks like this:
	+-------------------+
	| link/frame reg    | <- sp + 0x40
	| link/frame reg    | <- sp + 0x30
	| ... unused ...    | 
	| buffer end        | <- sp + 0x28
	| ...               |
	| buffer start      | <- sp + 0x18
	| size_t string len | <- sp + 0x10
	| long a (param 1)  | <- sp + 0x8
	| long b (param 2)  | <- sp
	+-------------------+
*/
_myadd:
	// Prepares the stack frame
	sub sp, sp, #0x40
	// store the frame register and link register
	stp x29, x30, [sp, #0x30]
	add x29, sp, #0x30
	
	// collect arguments (long, long)
	str x0, [sp, #0x8]  
	str x1, [sp]

	// start prepare arguments for _tostring
	add x0, sp, #0x18 // pointer to the address in our stack
	mov x1, #0x10 // size of the buffer

	// do the addition
	ldr x8, [sp, #0x8]
	ldr x9, [sp]
	add x2, x8, x9	

	// call _tostring, 
	// the result will be stored in the buffer
	// the actual size will be in x0 after the call
	// sets x30 to pc + 4 (return address)
	bl _tostring
	str x0, [sp, #0x10]

	// syscall to write the buffer to stdout
	mov x0, #1
	add x1, sp, #0x18
	ldr x2, [sp, #0x10]
	add x2, x2, #0x1
	mov x16, #4
	svc 0

	// restore the link register and frame pointer
	ldp x29, x30, [sp, #0x30]

	// destroy the current stack frame
	add sp, sp, #0x40
	ret


.global _reverse
.align 4
_reverse:
	// prepare the stack frame
	sub sp, sp, #0x10

	// collect arguments (char *, size_t)
	str x0, [sp, #0x8]
	str x1, [sp]

	// load the arguments in to registers
	ldr x8, [sp, #0x8]
	ldr x9, [sp]

	// use registers as the index counters (start and end)
	mov x10, #0
	sub x11, x9, #1

_reverse_loop:
	cmp x10, x11
	// skip the loop if the start index is greater than the end index
	b.ge _reverse_end

	// swap the characters
	// using the load byte and store byte instructions
	ldrb w12, [x8, x10]
	ldrb w13, [x8, x11]
	strb w13, [x8, x10]
	strb w12, [x8, x11]

	// increment and decrement counters
	add x10, x10, #1
	sub x11, x11, #1

	// jump back to the loop
	b _reverse_loop

_reverse_end:
	// destroy the stack frame
	add sp, sp, #0x10
	ret
