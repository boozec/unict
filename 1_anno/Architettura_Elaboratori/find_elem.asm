array	dcd		1, 3, 2, 4, 0
arr_n	dcd		5
elem		dcd		3
		
		mov		r0,  #arr_n
		ldr		r1, [r0] ; r1 <- lunghezza array
		
		mov		r0, #elem
		ldr		r2, [r0] ; r2 <- elemento da cercare
		
		mov		r0, #array ; r0 <- puntatore al primo elemento dell'array
		
loop
		cmp		r1, #0
		beq		loop_end
		
		ldr		r3,	 [r0]
		
		cmp		r3, r2
		beq		found
		
		add		r0, r0, #4
		sub		r1, r1, #1
		
		
		b		loop
		
found
		mov		r4, #0 ; r4 = 1, quindi trovato
		end
		
loop_end
		mov		r4, #1 ; r4 = 0, quindi non trovto
		end
