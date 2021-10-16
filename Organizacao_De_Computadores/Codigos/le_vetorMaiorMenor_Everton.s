	.data
txt_tamanho:	.asciiz		"\nEntre com o tamanho do vetor: "
txt_entrada:	.asciiz		"\nEntre com o elemento de indice "
txt_2pontos:	.asciiz		": "
txt_maior:	.asciiz		"\nMaior valor: "
txt_menor:	.asciiz		"\nIndice do menor valor: "
vetor: 		.space		400   # tamanho máximo 100 inteiros

	.text
main:
	add $s2, $zero, $ra		# salva endereço de retorno
	li $v0, 4
	la $a0, txt_tamanho
	syscall					#Imprime string

	li $v0, 5
	syscall					#Le tamanho do vetor
	add $s1, $zero, $v0		# e copia em $s1
	add $a1, $zero, $v0		# e também em $a1

	la $t0, vetor

	add $t1, $zero, $zero	#Inicializa variavel de controle (contador) do laco $t1

laco:
	slt $t2, $t1, $s1  # Se contador < quantidade entra no corpo do laço
	beq $t2, $zero, fim_leitura # senão pula para fim

	li $v0, 4
	la $a0, txt_entrada
	syscall					#Imprime string

	li $v0, 1
	add $a0, $zero, $t1
	syscall					#Imprime indice

	li $v0, 4
	la $a0, txt_2pontos
	syscall					#Imprime ":"

	li	$v0, 5
	syscall					#Le elemento do vetor

	sw $v0, 0 ($t0)		#Le armazena na memória em vetor[i]

	addi $t0, $t0, 4		#aponta para a proxima posição do vetor
	addi $t1, $t1, 1		#atualiza variável de controle
	j laco					# volta para testar novamente

seta_menor:
	add $t2, $zero, $t3
	add $v1, $zero, $t1
	j menor

menor:
	addi $t1, $t1, 1	   	#atualiza contador
	slt $t3, $t1, $a1		#compara se é o fim do vetor
	beq $t3, $zero, volta
	addi $t0, $t0, 4		#desloca para proxima posição do vetor

	lw $t3, 0($t0)

	slt $t4, $t2, $t3
	beq $t4, $zero, seta_menor

	j menor

seta_maior:
	add $v0, $zero, $t3
	j maior

maior:
	addi $t1, $t1, 1	   	#atualiza contador
	slt $t3, $t1, $a1		#compara se é o fim do vetor
	beq $zero, $t3, volta
	addi $t0, $t0, 4		#desloca para proxima posição do vetor

	lw $t3, 0($t0)

	slt $t4, $v0, $t3
	bne $t4, $zero, seta_maior

	j maior

volta:
	jr $ra

inicializa:
	add $t1, $zero, $zero	#incializa o contador
	lw $t5, 0($t0)			#coloca o valor do vetor[0] em $t5
	jr $ra

fim_leitura:
	la $a0, vetor			#coloca endereço de vetor0 em $a0
	add $t0, $zero, $a0

	jal inicializa

	addi $v1, $zero, 0     #seta o indice do menor como 0
	add $v0, $zero, $t5		#seta o maior como o primeiro elemento
	add $t2, $zero, $t5		#seta o menor valor como o primeiro elemento

	jal menor
	la $t0, vetor		#coloca novamente o endereço vetor0 em a0
	jal inicializa
	jal maior			# tirar o comentário para fazer a chamada da função


	add $s0, $zero, $v0		# copia resultados para $s0 e $s1
	add $s1, $zero, $v1

	li $v0, 4				#imprime texto
	la $a0, txt_maior
	syscall

	li $v0, 1				#imprime maior valor
	move $a0, $s0
	syscall

	li $v0, 4				#imprime texto
	la $a0, txt_menor
	syscall

	li $v0, 1				#mostra indice do menor valor
	move $a0, $s1
	syscall

	jr $s2					#retorna para quem chamou a função main
