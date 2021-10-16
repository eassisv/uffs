	.data
vetor1:		.space 400
vetor2:     .space 400
vetor3:		.space 400
txt_barran: 	.asciiz "\n"
txt_entrada:	.asciiz "Digite o tamanho do vetor: "
txt_2pts:	.asciiz ": "
txt_vt1:	.asciiz "Digite para o vetor A o valor do indice "
txt_vt2:	.asciiz "Digite para o vetor B o valor do indice "

	.text
main:
	li $v0, 4
	la $a0, txt_entrada
	syscall
	
	li $v0, 5
	syscall
	add $t0, $zero, $v0  #armazena o tamanho do vetor
	
	la $a1, vetor1
	la $a2, vetor2
	la $a3, vetor3
	
	addi $s0, $zero, 0	#inicializa um contador
	
le_vetor1:
	slt $s1, $s0, $t0
	beq $s1, $zero, vetor2_inicia

	li $v0, 4
	la $a0, txt_vt1
	syscall
	li $v0, 1
	add $a0, $zero, $s0
	syscall
	li $v0, 4
	la $a0, txt_2pts
	syscall
	li $v0, 5
	syscall
	
	sw $v0, 0($a1)	#armazena o valor digitador na posicao i do vetor A
	
	addi $s0, $s0, 1
	addi $a1, $a1, 4
	
	j le_vetor1

vetor2_inicia:
	addi $s0, $zero, 0

le_vetor2:
	slt $s1, $s0, $t0
	beq $s1, $zero, vetor3_inicia

	li $v0, 4
	la $a0, txt_vt2
	syscall
	li $v0, 1
	add $a0, $zero, $s0
	syscall
	li $v0, 4
	la $a0, txt_2pts
	syscall

	li $v0, 5
	syscall
	
	sw $v0, 0($a2) #armazena os valores do vetor B

	addi $s0, $s0, 1
	addi $a2, $a2, 4
	
	j le_vetor2

vetor3_inicia:
	addi $s0, $zero, 0
	la $a1, vetor1
	la $a2, vetor2

compara:
	slt $s1, $s0, $t0
	beq $s1, $zero, mostra_C
	
	lw $s2, 0($a1) 	#carrega os iesimos valores dos vetores A e B
	lw $s3, 0($a2)
	
	beq $s2, $s3, igual
	slt $s4, $s3, $s2
	beq $s4, $zero, menor
	
	sw $s4, 0($a3)
	
caminha_vetor:
	addi $a1, $a1, 4
	addi $a2, $a2, 4
	addi $a3, $a3, 4
	addi $s0, $s0, 1
	j compara
				
igual:
	addi $s4, $zero, 0
	sw $s4, 0($a3)
	
	j caminha_vetor
	
menor:
	addi $s4, $zero, -1
	sw $s4, 0($a3)
	
	j caminha_vetor

mostra_C:
	addi $s0, $zero, 0
	la $a3, vetor3
	
loop_C:
	slt $s1, $s0, $t0
	beq $s1, $zero, finaliza
	
	li $v0, 1
	lw $a0, 0($a3)
	syscall
	
	li $v0, 4
	la $a0, txt_barran #quabra a linha para o proximo valor
	syscall
	
	addi $s0, $s0, 1
	addi $a3, $a3, 4
	
	j loop_C

finaliza:
	li $v0, 10
	syscall
	
		
	