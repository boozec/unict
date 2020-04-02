array	dcd		1, 24, 0, 12, 24, 2, 24, 24
arr_n	dcd		8
elem		dcd		24
		
		mov		r0, #arr_n
		ldr		r1, [r0] ; r1 = lunghezza array
		
		mov		r0, #elem
		ldr		r2, [r0] ; r2 = elemento da controllare
		
		mov		r0, #array
		mov		r4, #0 ; r4 = contatore delle occorrenze
		
loop
		cmp		r1, #0
		beq		loop_end
		
		ldr		r3, [r0] ; r3 = valore in cui punta r0
		cmp		r3, r2
		beq		found
		
loop_back
		add		r0, r0, #4 ; r0 punta alla nuova word
		sub		r1, r1, #1
		
		b		loop
		
found
		add		r4, r4, #1
		b		loop_back
		
loop_end
		end
