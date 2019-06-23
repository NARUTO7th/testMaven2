#
#CSI 333.Programming at the Hardware-Software Interface
#Spring 2019
#supervisor: HuangYing
#ZR1704
#id:2017215193
#Tang Hao
#
		.data
prompt: 	.asciiz "Enter the line? "

Num:	.asciiz "No. of integers: "

promptOf1snum:	.asciiz "\nMaximum number of 1¡¯s in the binary representation: "			

maximunB:		.asciiz "\nIntegers of maximum number of 1¡¯s in the binary representation: \n"

newline:		.asciiz "\n"
				
input:		.space 80		#array of bytes of size 80

#integers:		.word 786,-1
integers:		.word 0:40	#array of words of size 40, will save the actual values of integers

cstack:		.byte 0:80	#Space for the character stack.

iArray:		.word 0:40	#the number of 1s' array 

intMaximum:	.word 0:40	#store number with max number of 1s'

msg_1_emptyline:	.asciiz	"Empty line"

	.text	
#to check if input is all white-spaces, if so, the program terminates	
main:	jal subroutine_1
#construct integers	
	jal subroutine_2
#print number of integers	
	jal subroutine_3
#print the maximum number of '1' bits	
	jal subroutine_4
#print integers with max. number of '1' bits 	
	jal subroutine_5
	j end
	
subroutine_1:	la $a0, prompt		#print out the prompt
		li $v0, 4
		syscall
	
		la $a0, input
		la $a1, 80                            
		li $v0, 8			#1.	input <- read 
		syscall
		
		la $s1,input			# $s1 = adress of input
		addi $t0, $0, 1			# $t0 = 1
		addi $t1, $0, '0'		# $t1 = '0'
		addi $t2, $0, '\n'		# $t2 = '\n'
		addi $t3, $0, '\t'		# $t3 = '\t'
		addi $t4, $0, ' '		# $t4 = ' '
		addi $t5, $0, 9			# $t5 = 9
		
	sub_1:	lb $s0, 0($s1)		 #check empty line $s0 = adress of input
		addi $s1, $s1, 1		
		beq $s0, $t2, sub_1
		beq $s0, $t3, sub_1
		beq $s0, $t4, sub_1
		beq $s0, $0, print_1
		jr $ra			#return to main
#to convert ASCII code representation of digits to actual integers, 
#49 is the ASCII code of '1', 53 is for '5', so 15 will be saved as word 
#instead of 49 and 53 as two bytes.
#		$s0 = C
#		$s1 = adress of input
#		$s2 = 0 (initialized) = E
#		$s3 = sum
#		$s4 = $s0 - 48
#		$t7 = D * P

subroutine_2:	la $s1, input
		# $t7 = stack pointer
		la $t7, cstack			#Initialize char stack pointer
		#base of array into register $t8
		la $t8, integers	
		move $a2, $0
		sw $ra, 0($sp)			 #Push $31 on stack.	
		addi $sp, $sp, -4
	step1:	lb $s0, 0($s1)		#1.	load the first/next byte from input as C 
		addi $s1, $s1, 1
		beq $s0, $0, step19	#2.	if C is the end of the line, goto step 19 
		
		sub $s4, $s0, $t1		#	|	
		slt $t6, $s4, $0		#	|
		beq $t6, $t0, step1
		slt $t6, $t5, $s4		#	v
		beq $t6, $t0, step1		#3.	if C is not a digit goto step 1		
		li $s2, 0			# E = 0
	step5:	sub $s0, $s0, 48		# C = C - 48
		addi $s2, $s2, 1		# E = E + 1
		jal push			#Push char in $3 on stack
		lb $s0, 0($s1)		#load next byte from input as C	
		addi $s1, $s1, 1
		
		sub $s4, $s0, $t1		#	|
		slt $t6, $s4, $0		# 	|
		beq $t6, $t0, step10	#0 <= c <= 9, goto step5
		slt $a3, $t5, $s4		# 	|
		beq $a3, $t0, step10	#	v
		j step5			#9.	if C is a digit then goto step 5	
		
	step10:	sub $s1, $s1, 1	#make address of input correct
		li $s3, 0		# sum = 0
		li $s5, 1		# P = 1
		li $s6,10		# R = 10
		
	step11:	beq $s2, $0, step17	#11.	if E == 0, goto step 17
		addi $s2, $s2, -1	#12.	E = E - 1
		jal pop			#13.	$v1 = D
		mul $a0, $v1, $s5	# D * P
		addu $s3, $s3, $a0	#14.	sum = sum + D * P 
		mul $s5, $s5, $s6	#15.	P = P * R 
		j step11
	step17:	sw $s3, ($t8)		#17.	save sum in integers
		addi $t8, $t8, 4 
		j count_numofInteger
		j step1			#18.	get ready for the digits of the next integer
	step19:	li $t9, -1
		sw $t9, ($t8)
		
		lw $ra, 4($sp)		#Restore $31 and pop stack.
		addi $sp, $sp, 4
		jr $ra			#20.	return to main
		
		
count_numofInteger:addi $a2, $a2, 1
    		j step1

#to count and print number of integers, here is 5 		    		
subroutine_3:    	la $a0, Num		#print out the prompt
		li $v0, 4
		syscall
	
		move $a0, $a2
		li $v0, 1
		syscall
		jr $ra 

#subroutine 4 
#		$s0 = address of integers
#		$s1 = elements of integers
#		$s2 = the result of "andi"
#		$s3 = -1
#		$a3 = number of 1s
#		$s4 = maximum of number of 1s
#		$t6 = whether s4 < s3
#
#		$t0 = 1
	
subroutine_4:	li $t0, 1				# $t0 = 1
		move $a3, $0
		move $s4, $0
		la $s5, iArray
		li $s3, -1
		la $s0, integers
	sub4_3:	lw $s1, 0($s0)
		beq $s1, $s3, sub4_5		#array's iteration is over
		addi $s0, $s0, 4
	sub4_1:	beq $s1, $0, sub4_2			#move integer instead of 1
		and $s2, $s1, 1
		beq $s2, $t0, count_numOf1s
	sub4_6:	srl $s1, $s1, 1
		j sub4_1
	sub4_2:	sw $a3, ($s5)
		addi $s5, $s5, 4
		slt $t6, $s4, $a3
		beq $t6, $t0, sub4_4
		beq $s4, $a3, sub4_4
		li $a3, 0
		beq $t6, $0, sub4_3
	sub4_4: 	move $s4, $a3
		li $a3, 0
		j sub4_3
		
	sub4_5:	la $a0, promptOf1snum	#print out the prompt
		li $v0, 4
		syscall
	
		move $a0, $s4
		li $v0, 1
		syscall
		jr $ra	
		
count_numOf1s:	addi $a3, $a3, 1
		j sub4_6	
		
	    		
 #subroutine 5
#use integers and iArray to print integers with max. number of '1' bits
#	$s3 = elements of integers
#	$s4 = elements of iArray
#	$s5 = elements of intMaximum
#	$t0 = maximum number of '1' bits				
subroutine_5:	la $s0, integers
		la $s1, iArray
		la $s2, intMaximum
		move $t0, $0	#maximum number of '1' bits
		move $t3, $0	#the number of elements in intMaximum
		li $t5, -1
		
		
		
	sub5_1:	lw $s3, ($s0)	#elements of integers
		lw $s4, ($s1)	#elements of iArray
		beq $s3, $t5, sub5_4
		
		addi $s0, $s0, 4
		addi $s1, $s1, 4													
		slt $t1, $t0, $s4
		li $t2, 1
		beq $t2, $t1, sub5_2	#current > previous alternate all elements
		beq $t0, $s4, sub5_3	#current = previous add elements
		j sub5_1
		
	sub5_2:	move $t0, $s4	#determine to clear array or keep add elements
		beq $t3, $0, sub5_3
		mul $t4, $t3, 4
		sub $s2, $s2, $t4	#shift the pointer to clear the intMaximum array
		li $t3, 0
	
	sub5_3:	sw $s3, ($s2)	#add one element to intMaximum
		addi $s2, $s2, 4
		addi $t3, $t3, 1
		j sub5_1
	
	sub5_4:	la $a0, maximunB		
		li $v0, 4
		syscall
	
		move $t6, $s2
		la $s2, intMaximum
		
print_loop:	lw $t7, ($s2)
		beq $s2, $t6, sub5_5
		addi $s2, $s2, 4
		
		move $a0, $t7
		li $v0, 1
		syscall
		
		la $a0, newline		
		li $v0, 4
		syscall
		
		j print_loop
	
	sub5_5:	jr $ra

		
				

#Procedure push: The character to be pushed is in the last byte of $3.
#Does not check for stack overflow.

push: 		sb $s0, 0($t7) 		#$15 used as stack pointer for char stack.
		addi $t7, $t7, 1 		#Increment char stack pointer by 1.
		jr $ra
		
#Procedure pop: The popped character is in the last byte of $3.
#Does not check for stack underflow.
pop: 		addi $t7, $t7, -1
		lbu $v1, 0($t7)
		jr $31		

print_1:	la $a0, msg_1_emptyline
		li $v0, 4
		syscall				
		
end:	li $v0, 10
	syscall



