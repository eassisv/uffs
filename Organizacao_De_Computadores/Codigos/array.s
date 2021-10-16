	.data
array1:		.space 12
space: 		.asciiz " "
	.text
main:
	la $t0, array1
	li $t1, 5
	sw $t1, ($t0)
	li $t1, 13
	sw $t1, 4($t0)
	li $t1, -7
	sw $t1, 8($t0)
	
	li $v0, 1
	lw $a0, ($t0)
	syscall
	
	li $v0, 4
	la $a0, space
	syscall
	
	li $v0, 1
	lw $a0, 4($t0)
	syscall
	
	li $v0, 4
	la $a0, space
	syscall
	
	li $v0, 1
	lw $a0, 8($t0)
	syscall
	
	li $v0, 10
	syscall