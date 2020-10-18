array1			dcd		1, 3, 4, 1
array2			dcd		1, 0, 2, 0
arrayn			dcd		4
			
			mov		r0, #arrayn
			ldr		r0, [r0]		; r0 = lunghezza array
			
			mov		r1, #array1     	; r1 = puntatore al primo array
			mov		r2, #array2     	; r2 = puntatore al secondo array
			
loop
			cmp		r0, #0
			beq		loop_end
			
			ldr		r3, [r1]		; r3 = valore a cui punta r1
			ldr		r4, [r2]		; r4 = valore a cui punta r2
			
			cmp		r3, #0			; se r3 è 0, la moltiplicazione sarà 0
			beq		r3_store
			blt		after_neg3	    	; se r3 è negativo, cambia il filtro a 1
jp_before4
			cmp		r4, #0		    	; se r4 è 0, la moltiplicazione sarà 0
			beq		r4_store
			blt		after_neg4		; se r4 è negativo, controlla se il filtro è già 1, in caso lo cambia
jp_after4
			cmp		r3, r4			; confronta r3 e r4 per fare la moltiplicazione con ciclo minore
			bgt		mul_r3
			ble		mul_r4
			
loop_back
			add		r1, r1, #4	    	; incrementa i puntatori e decrementa contatore
			add		r2, r2, #4
			sub		r0, r0, #1
			mov		r6, #0
			
			b		loop
			
after_neg3
			mvn		r3, r3
			add		r3, r3, #1
			mov		r6, #1
			b		jp_before4
			
restart_r6
			mov		r6, #0
			b		jp_afte4
			
after_neg4
			mvn		r4, r4
			add		r4, r4, #1
			cmp		r6, #1
			beq		restart_r6 		; re inserisce il valore 0 perché fa prodotto di due negativi
			
			mov		r6, #1
			b		jp_after4
			
neg3
			mvn		r3, r3
			add		r3, r3, #1
			add		r5, r5, r3
			b		loop_back
			
r3_store
			cmp		r6, #1
			beq		neg3
			str		r3, [r1]
			add		r5, r5, r3
			b		loop_back
			
neg4
			mvn		r4, r4
			add		r4, r4, #1
			str		r4, [r1]
			add		r5, r5, r4
			b		loop_back
			
r4_store
			cmp		r6, #1
			beq		neg4
			str		r4, [r1]
			add		r5, r5, r4
			b		loop_back
			
mul_r3
			cmp		r4, #1
			ble		r3_store
			
			add		r3, r3, r3
			
			sub		r4, r4, #1
			b	    	mul_r3
			
mul_r4
			cmp		r3, #1
			ble		r4_store
			
			add		r4, r4, r4
			
			sub		r3, r3, #1
			b		mul_r4
			
loop_end
			end
