num	dcd		27		; 0b11011
		
		mov		r0, #num
		ldr		r0, [r0]
		mov		r2, r0
		
		mov		r1, #32
		
loop
		and		r4, r2, #1
		cmp		r4, #1
		bne		itszero
		add		r3, r3, #1
itszero
		lsr			r2, r2, #1
		sub		r1, r1, #1
		cmp		r1, #0
		bne		loop
		
		end
