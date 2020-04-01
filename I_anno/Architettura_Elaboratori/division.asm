op_a		dcd		42
op_b		dcd		6
		
		mov		r0,	 #op_a
		ldr		r1, [r0]
		
		mov		r0, #op_b
		ldr		r2, [r0]
		
		mov		r0, #0
		
loop
		cmp		r1, r2
		blt		loop_end
		
		sub		r1, r1, r2
		add		r0, r0, #1
		
		b		loop
		
loop_end
		
		end
