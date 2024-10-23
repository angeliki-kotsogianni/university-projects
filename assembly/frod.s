	.text
main:
	lw $t1,A
	add $sp,$sp,-4 # Caller Saved Register $t1
	sw $t1,0($sp)
	move $a0,$t1 # print($t1)
	li $v0,1
	syscall
	jal sub1 # call sub1
	lw $t1,0($sp)
	add $sp,$sp,4
	move $a0,$t1 # print($t1)
	li $v0,1
	syscall
	li $v0,10
	syscall
sub1: move $a0,$t1 # print($t1)
	li $v0,1
	syscall
	li $a0,13 # print enter
	li $v0,11
	syscall
	li $t1,10
	jr $ra # return to main

	.data
A: .word 5