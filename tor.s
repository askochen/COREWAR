.name "TOR"
.comment "I'm strong!!!"


	sti		r1, %:l1, %1
	sti		r1, %:l2, %1
	sti 	r1, %:l3, %1
	fork	%:l2
	sti		r1,%:l4,%1
	sti		r1,%:l1,%1
	sti		r1,%:l2,%1
	sti		r1,%:l3,%1
	sti		r1,%:l4,%1
	sti     r1, %:l5, %1
	sti     r1, %:l5, %9
	sti     r1, %:l5, %17


l1:
	live	%13
	ld		%0, r2
	zjmp	%:l1

l2:
	live	%13
	fork	%:l2
	live	%13
	fork	%:l3
	live	%13
	fork	%:l1
	live	%13
	fork	%:l3

l4:		live 	%13
	 	ld		%0, r2
		zjmp	%:l4
l3:
	live	%13
	fork 	%:l1	

l5:
	live	%13
	fork	%:l2

	live	%13
	ld		%0, r2
	zjmp	%:l1





