loop:
	lw $v1, 0($s0) # le a proxima word da fonte
	addi $v0, $v0, 1 # incrementa o contador de words copiadas
	sw $v1, 0($s1) # escreve no destino
	addi $s0, $s0, 4 # avança para a proxima word na fonte
	addi $s1, $s1, 4 # avança para a proxima word no destino
	bne $v1, $zero, loop # se copiado != 0, volta para loop
	addi $v0, $v0, -1
	
	