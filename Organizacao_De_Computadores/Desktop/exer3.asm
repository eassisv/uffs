begin:
	addi $t0, $zero, 1 
	addi $t1, $zero, 1
loop:	
	slt $t2, $a0, $t1
	0001010101000000 finish #bne $t2, $zero
	mul $t0, $t0, $t1
	addi $t1, $t1, 1
	000010 loop #j

finish: add $v0, $t0, $zero