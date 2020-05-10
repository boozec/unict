arr_n		dcd		6
array		dcd		3, 6, 7, 2, 9, 0
s_arr		dcd		1
			
			mov		r0, #arr_n
			ldr		r0, [r0]
			mov		r1, r0
			
			mov		r2, #s_arr
			mov		r1, #array
			mov		r4, #0		; number of elements on new sequence
			
loop
			cmp		r0, #0
			beq		end_program
			ldr		r3, [r1], #4
			cmp		r3, #5		; number to compare
			blt		data_store
subn_loop
			sub		r0, r0, #1
			b		loop
			
data_store
			str		r3, [r2], #4
			add		r4, r4, #1
			b		subn_loop
			
end_program
			str		r4, [r2]
			end
