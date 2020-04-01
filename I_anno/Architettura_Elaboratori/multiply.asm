op_1	dcd		4
op_2	dcd		10
		
		mov		r0, #op_1
		ldr		r1, [r0]
		
		mov		r0, #op_2
		ldr		r2, [r0]
		
		mov		r0, #0
		
loop
		cmp		r2, #0
		beq		loop_end
		
		add		r0, r0, r1
		sub		r2, r2, #1
		b		loop
		
loop_end
		end
