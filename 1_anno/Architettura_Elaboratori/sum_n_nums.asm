arr_1	dcd		3, 2, 1, 5
a_len	dcd		4
		
		mov		r0, #a_len
		ldr		r1, [r0] ; valore N, grandezza array
		
		mov		r0, #arr_1 ; puntatore dell'array
		ldr		r2, [r0] ; primo valore dell'array
		mov		r3, #0
		
loop
		cmp		r1, #0
		beq		loop_end
		
		add		r3, r3, r2
		add		r0, r0, #4 ; incrementa di un byte il puntatore dell'array
		ldr		r2, [r0]
		
		sub		r1, r1, #1
		b		loop
		
loop_end
		end
