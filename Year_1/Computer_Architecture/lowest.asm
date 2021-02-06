array	dcd		3, 6, 10, 55, -1, 120, 10, -2, 0, 0, 13
arr_n	dcd		12
		
		mov		r0, #arr_n
		ldr		r1, [r0] ; r1 = grandezza dell'array
		
		mov		r0, #array ; r0 = array[0]
		ldr		r3, [r0] ; r3 = numero maggiore
		
loop
		cmp		r1, #0
		beq		loop_end
		
		ldr		r2, [r0]
		
		cmp		r2, r3
		blt		assign_lt
		
		add		r0, r0, #4
		
loop_back
		sub		r1, r1, #1
		
		b		loop
		
assign_lt
		mov		r3, r2
		b		loop_back
		
loop_end
		end
