.text
		.globl main
		
main: 

	jal readOption
	move $t0, $v0
	sw $t0, op
	
while_loop:

	blt $t0, 1, end_while
	bgt $t0, 8, end_while
	
	beq $t0, 1, case_1
	beq $t0, 2, case_2
	beq $t0, 3, case_3
	beq $t0, 4, case_4
	beq $t0, 5, case_5
	beq $t0, 6, case_6
	beq $t0, 7, case_7
	beq $t0, 8, case_8
	
	j while_loop
	
case_1: 
	la $a0, strA
	li $v0, 4
	syscall
	
	la $a0, pinA
	li $a1, 10
	jal readPin
	
	j end_cases
	
case_2:
	la $a0, strB
	li $v0, 4
	syscall
	
	la $a0, pinB
	li $a1, 10
	jal readPin
	
	j end_cases

case_3:
	la $a0, strPA
	li $v0, 4
	syscall
	
	lw $t0, mikosA
	
	la $a0, pinA
	la $a1, sparseA
	jal createSparse
	
	move $t0, $v0
	
	div $t0, $t0, 2
	
	move $a0, $t0
	li $v0, 1
	syscall
	
	la $a0, str_values
	li $v0, 4
	syscall
	
	j end_cases
	
case_4:
	la $a0, strPB
	li $v0, 4
	syscall
	
	lw $t0, mikosB
	
	la $a0, pinB
	la $a1, sparseB
	jal createSparse
	
	move $t0, $v0
	
	div $t0, $t0, 2
	
	move $a0, $t0
	li $v0, 1
	syscall
	
	la $a0, str_values
	li $v0, 4
	syscall
	
	j end_cases
	
case_5:
	la $a0, strC
	li $v0, 4
	syscall
	
	lw $t0, mikosC
	
	lw $t1, mikosA
	add $sp, $sp, -4
	sw $t1, 0($sp)
	
	la $a0, sparseC
	la $a1, SparseA
	
	la $a2, mikosB
	la $a3, SparseB
	
	jal addSparse
	
	move $t0, $v0
	
	div $t0, $t0, 2
	
	sw $t0, mikosC
	
	move $a0, $t0
	li $v0, 1
	syscall
	
	la $a0, str_values
	li $v0, 4
	syscall
	
	j end_cases
	
case_6:
	la $a0, strDA
	li $v0, 4
	syscall
	
	la $a0, sparseA
	la $a1, mikosA
	
	jal printSparse
	j end_cases
	
case_7:
	la $a0, strDB
	li $v0, 4
	syscall
	
	la $a0, sparseB
	la $a1, mikosB
	
	jal printSparse
	j end_cases
	
case_8:
	la $a0, strDC
	li $v0, 4
	syscall
	
	la $a0, sparseC
	la $a1, mikosC
	
	jal printSparse
	j end_cases

end_cases:
	jal readOption
	move $t0, $v0
	sw $t0, op
	j while_loop
	
end_while:
	li $v0,10
	syscall


readPin:

    add $sp, $sp, -4
    sw $t2, 0($sp)

    li $t2, 0
	
	move $t3, $a0

read_array_loop:
    bge $t2, $a1, exit_read_array 
   
    li $v0, 4
    la $a0, position_prompt
    syscall
	
    move $a0, $t2
    li $v0, 1
    syscall

    la $a0, separetor_prompt
    li $v0, 4
    syscall

    li $v0, 5 
    syscall
    sw $v0, ($t3)
	addi $t3, $t3, 4
	
    addi $t2, $t2, 1

    j read_array_loop

exit_read_array:
    lw $t2, 0($sp)
    addi $sp, $sp, 4
    jr $ra 
	
		
createSparse:
    li $t0, 0      
    li $t1, 0    
   
    loop:
        bge $t0, $a1, end_loop  
       
        lw $t3, 0($a0)  
        beqz $t3, skip  
       
        sw $t0, 0($a2)  
        addi $a2, $a2, 4 
       
        sw $t3, 0($a2)  
        addi $a2, $a2, 4  
       
        addi $t1, $t1, 2
       
        skip:
        addi $t0, $t0, 1
        addi $a0, $a0, 4  
        j loop
       
    end_loop:
        move $v0, $t1
        jr $ra 
		
        



printSparse:
    li $t0, 0    
   
   loop1:
    bge $t0, $a1, end_loop1
       
    lw $t1, 0($a0) 
    addi $a0, $a0, 4 
       
    lw $t2, 0($a0)  
    addi $a0, $a0, 4 
       
    li $v0, 4       
    la $a0, position_string  
    syscall         

    move $a0, $t1 
    li $v0, 1      
    syscall         

    li $v0, 4       
    la $a0, value_string  
    syscall
       
    move $a0, $t2  
    li $v0, 1        
    syscall         

    li $v0, 4        
    la $a0, newline_string 
    syscall          
       
    addi $t0, $t0, 1
    j loop1
       
end_loop1:
    jr $ra 
		
		
readOption:
    li $v0, 4  
    la $a0, menu_separator 
    syscall  
   
    la $a0, menu_option_1  
    syscall  
   
   
    la $a0, menu_option_8  
    syscall  
   
    la $a0, menu_separator  
    syscall  
   
    la $a0, choice_prompt  
    syscall  
   
    li $v0, 5  
    syscall 
   
    jr $ra 
	
addSparse:
	lw $t1, 0($sp)
	add $sp, $sp, 4

	li $t0, 0
	li $t2, 0
	li $t3, 0
	bge $t0, $t1, end_for1
	bge $t2, $a2, end_for1
	lw $t4, 0($a1)
	lw $t5, 0($a3)
	addi $a1, $a1, 4
	addi $a3, $a3, 4
	bge $t4, $t5, else_if
	lw $t6, 0($a1)
	sw $t6, 0($a0)  
    addi $a1, $a1, 4
       
    sw $t3, 0($a1)  
    addi $a1, $a1, 4
	
	
	
	
	
end_for1:

end_loop:
	lw $t2, 0($sp)
    addi $sp, $sp, 4



.data 
position_prompt: .asciiz "Position "
separetor_prompt: .asciiz ": "
position_string: .asciiz "Position: "
value_string: .asciiz " Value: "
newline_string: .asciiz "\n"
menu_separator: .asciiz "\n-----------------------------\n"
menu_option_1: .asciiz "1. Read Array A\n"
choice_prompt: .asciiz "Choice? "
strr: .space 40
i: .word 0
mikosA: .word 0
mikosB: .word 0
mikosC: .word 0
op: .word 0
pinA: .space 40
pinB: .space 40
sparseA: .space 80
sparseB: .space 80
sparseC: .space 80
op: .word 0
strA: .asciiz "Reading Array A"
strB: .asciiz "Reading Array B"
strPA: .asciiz "Creating Sparse Array A"
strPB: .asciiz "Creating Sparse Array B"
str_values: .asciiz " values"
strC: .asciiz "Creating Sparse Array C = A + B"
strDA: .asciiz "Displaying Sparse Array A"
strDB: .asciiz "Displaying Sparse Array B"
strDC: .asciiz "Displaying Sparse Array C"