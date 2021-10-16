	.data
	
vetor:		.space 400
txt_entrada:	.asciiz "Digite o tamanho do vetor: "
txt_entradas: 	.asciiz "Digite os valores do vetor:\n"
txt_N: 		.asciiz "Digite o valor de N: "
txt_maior:	.asciiz "Quantos elementos sao maiores que N? "
txt_menor:	.asciiz "\nQuantos elementos sao menor que N? "
txt_iguais:	.asciiz "\nQuantos elementos sao iguais a N? "


	.text
main:
	li $v0, 4
	la $a0, txt_entrada
	syscall
	
	li $v0, 5
	syscall
	add $a1, $zero, $v0 	#colcoca em $a1 o tamanho do vetor
	
	li $v0, 4
	la $a0, txt_N
	syscall
	
	li $v0, 5
	syscall
	add $a2, $zero, $v0		#colocar em $a2 o valor de N
	
	addi $s0, $zero, 0      #inicializa os contadores
	addi $t0, $zero, 0		
	addi $t1, $zero, 0
	addi $t2, $zero, 0

	li $v0, 4
	la $a0, txt_entradas
	syscall
	
	la $a0, vetor
	
le_valores:
	slt $s2, $s0, $a1
	beq $s2, $zero, inicializa

	li $v0, 5
	syscall
	
	sw $v0, 0($a0)
	addi $a0, $a0, 4
	addi $s0, $s0, 1
	
	j le_valores
	
inicializa:
	addi $s0, $zero, 0		#inicializa o contador novamente
	la $a0, vetor

laco:
	slt $s2, $s0, $a1
	beq $s2, $zero, finaliza

	lw $s1, 0($a0)

	beq $s1, $a2, set_igual

	slt $s2, $a2, $s1
	beq $s2, $zero, set_menor
			
	slt $s2, $s1, $a2
	beq $s2, $zero, set_maior
	
finaliza:
	li $v0, 4
	la $a0, txt_maior
	syscall
	
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 4
	la $a0, txt_menor
	syscall

	li $v0, 1
	move $a0, $t1
	syscall
		
	li $v0, 4
	la $a0, txt_iguais
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
		
	li $v0, 10
	syscall

set_maior:
	addi $t0, $t0, 1
	
	addi $s0, $s0, 1
	addi $a0, $a0, 4
	
	j laco

set_menor:
	addi $t1, $t1, 1
	
	addi $s0, $s0, 1
	addi $a0, $a0, 4
	j laco

set_igual:
	addi $t2, $t2, 1
	
	addi $s0, $s0, 1
	addi $a0, $a0, 4
	j laco