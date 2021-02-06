arr_n		dcd		8
array		dcd		1, 2, 4, 6, -5, 8, 7, 3
s_arr		dcd		0
			
			mov		r0, #arr_n
			ldr		r0, [r0]
			mov		r1, r0
			
			mov		r4, #1		; 0 = even, 1 = odd
			mov		r6, #0		; number of elements on new sequence
			
			mov		r2, #s_arr
			
			mov		r1, #array
			
loop
			cmp		r0, #0
			beq		end_program
			ldr		r3, [r1], #4
			mov		r5, r3
			
			and		r5, r3, #1
			cmp		r5, r4		; check if element stored in r3 is odd or even
			beq		data_store
subn_loop
			sub		r0, r0, #1
			b		loop
			
data_store
			str		r3, [r2], #4
			add		r6, r6, #1
			b		subn_loop
			
end_program
			str		r6, [r2]
			end
