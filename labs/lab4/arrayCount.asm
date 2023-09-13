# arrayCount.asm
        .data
arrayA: .word 11, 0, 31, 22, 9, 17, 6, 9 # arrayA has 8 values
count:  .word 999                        # dummy value

        .text

main:
        # code to set up the variable mappings
                la $t0, arrayA          # &A[]
                addi $t1, $t0, 0        # &A[i]
                addi $t2, $t0, 28       # address of last element
                add  $s0, $zero, $zero  # final result in $s0
                lw $t8, count           # map count -> $t8, can use la too?
        
        # code for reading in the user value X
                li $v0, 5               # system call code for read_int
                syscall                 # call read string
                add $t3, $v0, $zero     # store number in $t3 (power-of-two)
        
        # code for counting multiples of X in arrayA
                add $t5, $t3, $zero     # creating the bitmask
        loop:   bge $t1, $t2, end
                lw $t4, 0($t1)          # $t4 is A[i]
                and $t6, $t4, $t5       # $t6 is remainder
                bne $t6, $zero, skip
                addi $s0, $s0, 1        # ans++
        skip:   addi $t1, $t1, 4        # moving to next element address
                j loop
        end:

        # code for printing result
                li $v0, 1               # system call code for print_int
                add $a0, $s0, $zero     # integer to print
                syscall                 # print the integer

        # code for terminating the program
        li $v0, 10
        syscall