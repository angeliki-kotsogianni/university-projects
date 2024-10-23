	.text
	.globl _start
	
_start: lw $a0, X
		li $v0, 1
		syscall
		
		li $v0, 10
		syscall
		
	.data
	
X: .word 10