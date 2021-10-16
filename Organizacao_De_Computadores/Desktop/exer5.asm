	.data
txt_entrada:			.asciiz "Digite o valor do indice "
txt_2pontos:			.asciiz ": "
txt_maior:			.asciiz "\nMaior numero: "
txt_menor:			.asciiz "\n\nMenor numero: "
txt_indice:			.asciiz "\nIndice: "
txt_diferenca:			.asciiz "\n\nDiferença entre maior e menor: "						
txt_maiores_diferenca:		.asciiz "\n\nQuantidade de elementos maiores que a diferença: "
txt_menores_diferenca:		.asciiz "\n\nQuantidade de elementos menores que a diferença: "										
																																
																		
	.text
main:
	addi $a0, $zero, 40
	li $v0, 9
	syscall
	
	move $s0, $v0 #s0 = inicio vetor
	
	add $t3, $zero, $s0 #incio aux
	add $t0, $zero, $zero #contador
	addi $t1, $zero, 10 #tamanho vetor
	
	jal imprime_texto_entrada 

	addi $a0, $zero, 8 #Aloca espaço para o maior e posicao
	li $v0, 9
	syscall
	
	move $s1, $v0 #Maior em s1

	addi $a0, $zero, 8 #Aloca espaço para o menor e posicao
	li $v0, 9
	syscall
	
	move $s2, $v0 #menor em s2
						
	li $v0, 5
	syscall
	
	#Inicia o maior e o menor com o primeiro valor lido
	sw $v0, 0 ($s1)
	sw $t0, 4 ($s1)

	sw $v0, 0 ($s2)
	sw $t0, 4 ($s2)	
	
	sw $v0, 0 ($t3)
	
le_valores:
	addi $t0, $t0, 1
	addi $t3, $t3, 4

	slt $t2, $t0, $t1
	beq $t2, $zero, calcula_diferenca
	
	jal imprime_texto_entrada
		
	li $v0, 5
	syscall
	
	sw $v0, 0 ($t3)
	
	lw $t4, 0 ($s1)
	bgt $v0, $t4, atualiza_maior
	lw $t4, 0 ($s2)
	blt $v0, $t4, atualiza_menor
	
	j le_valores
	

imprime_texto_entrada:
	li $v0, 4
	la $a0, txt_entrada
	syscall
	
	li $v0, 1
	add $a0, $zero, $t0
	syscall
	
	li $v0, 4
	la $a0, txt_2pontos
	syscall		
	
	jr $ra
	
atualiza_maior:
	sw $v0, 0 ($s1)
	sw $t0, 4 ($s1)

	j le_valores	

atualiza_menor:
	sw $v0, 0 ($s2)
	sw $t0, 4 ($s2)

	j le_valores	

calcula_diferenca:
	lw $t3, 0 ($s1)
	lw $t4, 0 ($s2)
	sub $s3, $t3, $t4 #diferenca entre maior e menor esta em s3
	
	add $t0, $zero, $zero #reinicia contador
	add $t3, $zero, $s0 #t3 recebe o inicio do vetor
	add $s4, $zero, $zero #inicia contador maior em 0
	add $s5, $zero, $zero #inicia contador menor em 0
	
maiores_menores_diferenca:
	slt $t2, $t0, $t1
	beq $t2, $zero, final

	lw $t4, 0 ($t3)

	bgt $t4, $s3, atualiza_contador_maior
	blt $t4, $s3, atualiza_contador_menor
		
	addi $t0, $t0, 1
	addi $t3, $t3, 4
		
	j maiores_menores_diferenca

atualiza_contador_maior:
	addi $s4, $s4, 1
	addi $t0, $t0, 1
	addi $t3, $t3, 4	
	
	j maiores_menores_diferenca
	
atualiza_contador_menor:
	addi $s5, $s5, 1
	addi $t0, $t0, 1
	addi $t3, $t3, 4
	
	j maiores_menores_diferenca
	
final:
	li $v0, 4
	la $a0, txt_maior
	syscall
	
	li $v0, 1
	lw $a0, 0 ($s1)
	syscall
	
	li $v0, 4
	la $a0, txt_indice
	syscall
	
	li $v0, 1
	lw $a0, 4 ($s1)
	syscall
	
	li $v0, 4
	la $a0, txt_menor
	syscall
	
	li $v0, 1
	lw $a0, 0 ($s2)
	syscall
	
	li $v0, 4
	la $a0, txt_indice
	syscall
	
	li $v0, 1
	lw $a0, 4 ($s2)
	syscall
	
	li $v0, 4
	la $a0, txt_diferenca
	syscall
	
	li $v0, 1
	add $a0, $zero, $s3
	syscall
	
	li $v0, 4
	la $a0, txt_maiores_diferenca
	syscall
	
	li $v0, 1
	add $a0, $zero, $s4
	syscall
	
	li $v0, 4
	la $a0, txt_menores_diferenca
	syscall
	
	li $v0, 1
	add $a0, $zero, $s5
	syscall	
	
	li $v0, 10
	syscall
	
	
