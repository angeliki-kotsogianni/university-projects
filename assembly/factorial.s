	.text
	.globl _start
	
_start:
	
	la $a0, warning #kalei thn printString gia na proeidopoihsei ton xrhsth na valei n <= 12 allios tha exume overflow
	li $v0, 4 #to warning xriazetai mono gia to n afu an valei k > n to programma den tha bei ston ypologismo tu k!
	syscall
	
	la $a0, ask1 #kalei thn printString gia na zitisei to n
	li $v0, 4
	syscall
	
	li $v0, 5 #kalei thn readInt gia to n
	syscall
	sw $v0, n
	
	lw $t0, n #fortonei to n ston $t0
	li $t1, 12 #fortonei to 12 ston $t1
	bgt $t0, $t1, exit_now #an n > 12 tote goto exit_now giati tha eixame overflow
	
	la $a0, ask2 #kalei thn printString gia na zitisei to k
	li $v0, 4
	syscall
	
	li $v0, 5 #kalei thn readInt gia to k
	syscall
	sw $v0, k
	
	lw $t1, n #pernaei ston $t1 to n
	lw $t2, k #ston $t2 to k
	bge $t1, $t2, l1 #an n >= k goto l1
	j l2 #an exei ftasei edo simainei oti n < k ara sto else kai goto l2
	
l1:	bltz $t2, l2 #an n>=k exei erthei edo kai elegxei an to k < 0 tote goto l2 diladi sto else allios sinexizei exontas bei sto if 

	lw $t1, fact_n #pernaei ston $t1 to fact_n(n!)
	lw $t0, i #pernaei ston $t0 to i
	lw $t5, n #ston $t5 to n
	
again1: #ilopoihsh ths for ws eksis:
	
	bgt $t0, $t5, exit1 #an i > 0 goto exit1 diladi vges apthn for
	mul $t1, $t1, $t0 #allios erxetai edo kai kanei fact_n *= i
	sw $t1, fact_n #kai pernaei thn timh
	add $t0, $t0, 1 #i = i + 1
	sw $t0, i
	j again1 #epanalipsi
	
exit1: #vgike apth for ara etimazetai gia to epomeno for
	
	lw $t2 fact_k
	li $t0, 1 #afto to kanw giati allios fortone to i me thn proigumeni timh pu eixe thn teleftaia fora pu to xrisimipoihsa ara eprepe na to ksanakanw 1
    sw $t0, i
	lw $t0, i
	lw $t1, k
	
again2: #me thn idia logiki...
	
	bgt $t0, $t1, exit2
	mul $t2, $t2, $t0
	sw $t2, fact_k
	add $t0, $t0, 1
	sw $t0, i
	j again2

exit2:

	lw $t3, fact_nk
	li $t0, 1
    sw $t0, i
	lw $t0, i
	lw $t1, n
	lw $t2, k
	sub $t4, $t1, $t2 #n - k ston $t4
	sw $t4, d #pernaei to n - k sthn d
	lw $t4, d

again3: 

	bgt $t0, $t4, exit3
	mul $t3, $t3, $t0
	sw $t3, fact_nk
	add $t0, $t0, 1
	sw $t0, i
	j again3
	
exit3: #teliosame me ta for ara emfanizume to teliko minima

	la $a0, final1
	li $v0, 4
	syscall
	
	lw $a0, n
	li $v0, 1
	syscall
	
	la $a0, final2
	li $v0, 4
	syscall
	
	lw $a0, k
	li $v0, 1
	syscall
	
	la $a0, final3
	li $v0, 4
	syscall
	
	#edo ginetai o ipologismos twn sindiasmwn afu exume vrei ta paragontika
	lw $t2, fact_k #ta fortonume stus registers
	lw $t3, fact_nk
	mul $t0, $t2, $t3 #fact_k * fact_nk ston $t0 to apotelesma
	lw $t1, fact_n #fortonume kai to $t1
	div $t0, $t1, $t0 #fact_n / (fact_k*fact_nk)
	move $a0, $t0 #to metaferume gia na to emfanisume
	li $v0, 1
	syscall
	
	li $v0, 10 #exit
	syscall
	
l2: la $a0, err #sto else
	li $v0, 4
	syscall
	
	li $v0, 10 #exit
	syscall
	
exit_now: 

	la $a0, overflow_error #emfanizei katallilo minima afu n > 12 kai termatizei to programma sth sinexeia
	li $v0, 4
	syscall
	
	li $v0, 10 #exit
	syscall
	
	.data
n:  .space 4
k:  .space 4
ask1: .asciiz "Enter number of objects in the set (n): "
ask2: .asciiz "Enter number to be chosen (k): "
err: .asciiz "Please enter n >= k >= 0"
fact_n: .word 1
fact_k: .word 1
fact_nk: .word 1
final1: .asciiz "C("
final2: .asciiz ", "
final3: .asciiz ") = "
i:	.word 1
d:	.word 0
warning: .asciiz "CAUTION! n MUST BE LESS OR EQUAL TO 12\n"
overflow_error: .asciiz "System requirement not met."
