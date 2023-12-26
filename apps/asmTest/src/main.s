.global _myadd 
.align 4
_myadd:
	sub sp, sp, #0x40
	stp x29, x30, [sp, #0x30]
	add x29, sp, #0x30
	str x0, [sp, #0x8]
	str x1, [sp]

	add x0, sp, #0x18
	mov x1, #0x10

	ldr x8, [sp, #0x8]
	ldr x9, [sp]
	add x2, x8, x9	
	bl _tostring
	str x0, [sp, #0x10]

	mov x0, #1
	add x1, sp, #0x18
	ldr x2, [sp, #0x10]
	add x2, x2, #0x1
	mov x16, #4
	svc 0

	ldp x29, x30, [sp, #0x30]
	add sp, sp, #0x40
	ret


.global _reverse
.align 4
_reverse:
	sub sp, sp, #0x10
	str x0, [sp, #0x8]
	str x1, [sp]

	ldr x8, [sp, #0x8]
	ldr x9, [sp]
	mov x10, #0
	sub x11, x9, #1

_reverse_loop:
	cmp x10, x11
	b.ge _reverse_end

	ldrb w12, [x8, x10]
	ldrb w13, [x8, x11]
	strb w13, [x8, x10]
	strb w12, [x8, x11]

	add x10, x10, #1
	sub x11, x11, #1
	b _reverse_loop

_reverse_end:
	add sp, sp, #0x10
	ret
