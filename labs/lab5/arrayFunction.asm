# arrayFunction.asm
       .data 
array: .word 8, 2, 1, 6, 9, 7, 3, 5, 0, 4
newl:  .asciiz "\n"

       .text
main:
	# Print the original content of array
	# setup the parameter(s)
	la $a0, array	# $a0 = address of first element in array
	li $a1, 10		# $a1 = num elements in array

	# call the printArray function
	jal printArray    # Make a function call to printArray()

	# Ask the user for two indices
	li   $v0, 5         	# System call code for read_int
	syscall           
	addi $t0, $v0, 0    	# first user input in $t0
 
	li   $v0, 5         	# System call code for read_int
	syscall           
	addi $t1, $v0, 0    	# second user input in $t1

	# Call the findMin function
	# setup the parameter(s)
	la   $a0, array		# $a0 = address of first element in array
	
	sll $t1, $t1, 2
	add $a1, $a0, $t1	# a1 = address of A[y]
	
	sll $t0, $t0, 2
	add $a0, $a0, $t0	# a0 = address of A[x]

	# call the function
	jal findMin    # Make a function call to findMin()


	# Print the min item
	# place the min item in $t3	for printing
	lw $t3, 0($v0)

	# OWN ADD IN : store the address of minimum item!
	addi $s0, $v0, 0

	# Print an integer followed by a newline
	li   $v0, 1   		# system call code for print_int
    addi $a0, $t3, 0    # print $t3
    syscall       		# make system call

	li   $v0, 4   		# system call code for print_string
    la   $a0, newl    	# 
    syscall       		# print newline

	#Calculate and print the index of min item
	la   $a0, array		# $a0 = address of first element in array
	sub $t0, $s0, $a0	# difference in address ; rmb : $s0 is stored address of min element
	srl $t0, $t0, 2		# /4 to get index

	# Place the min index in $t3 for printing	
	addi $t3, $t0, 0

	# Print the min index
	# Print an integer followed by a newline
	li   $v0, 1   		# system call code for print_int
    addi $a0, $t3, 0    # print $t3
    syscall       		# make system call
	
	li   $v0, 4   		# system call code for print_string
    la   $a0, newl    	# 
    syscall       		# print newline
	
	# End of main, make a syscall to "exit"
	li   $v0, 10   		# system call code for exit
	syscall	       		# terminate program
	

#######################################################################
###   Function printArray   ### 
#Input: Array Address in $a0, Number of elements in $a1
#Output: None
#Purpose: Print array elements
#Registers used: $t0, $t1, $t2, $t3
#Assumption: Array element is word size (4-byte)
printArray:
	addi $t1, $a0, 0	# $t1 is the pointer to the item
	sll  $t2, $a1, 2	# $t2 is the offset beyond the last item
	add  $t2, $a0, $t2 	# $t2 is pointing beyond the last item
l1:	
	beq  $t1, $t2, e1
	lw   $t3, 0($t1)	# $t3 is the current item
	li   $v0, 1   		# system call code for print_int
    addi $a0, $t3, 0   	# integer to print
    syscall       		# print it
	addi $t1, $t1, 4
	j    l1				# Another iteration
e1:
	li   $v0, 4   		# system call code for print_string
    la   $a0, newl    	# 
    syscall       		# print newline
	jr   $ra			# return from this function


#######################################################################
###   Student Function findMin   ### 
#Input: Lower Array Pointer in $a0, Higher Array Pointer in $a1
#Output: $v0 contains the address of min item 
#Purpose: Find and return the minimum item 
#              between $a0 and $a1 (inclusive)
#Registers used: $t0, $t1, $t2, $t3, $t4
#Assumption: Array element is word size (4-byte), $a0 <= $a1
findMin:
	addi $t1, $a0, 0	# $t1 is the pointer to the lower item
	addi $t2, $a1, 0 	# $t2 is pointing beyond the higher item
	addi $v0, $t1, 0	# $v0 = &min, let &min be &first item
l2:
	beq  $t1, $t2, e2
	lw   $t0, 0($v0)	# $t0 be min item
	lw   $t3, 0($t1)	# $t3 is current item
	slt  $t4, $t3, $t0  # if curr item < min, $t4 = 1
	beq  $t4, $0, c	    # if curr item > min, continue
	addi $v0, $t1, 0	# else &min = &curr item
c:
	addi $t1, $t1, 4
	j    l2				# Another iteration
e2:
	jr $ra				# return from this function