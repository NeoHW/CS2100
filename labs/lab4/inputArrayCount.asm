# arrayCount.asm
        .data
arrayA: .word 11, 0, 31, 22, 9, 17, 6, 9 # arrayA has 8 values
count:  .word 999                        # dummy value

        .text

main:
        # code to set up the variable mappings
                la $t0, arrayA          # &A[]
                addi $t1, $t0, 0        # &A[i]
                addi $t2, $t0, 32       # address of last element
                add  $s0, $zero, $zero  # final result in $s0
                lw $t8, count           # map count -> $t8
        
        # code for reaing in 8 values from user
        loop1:  bge $t1, $t2, end1
                li $v0, 5               # system call code for read_int
                syscall                 # call read string
                sw $v0, 0($t1)          # store number in $A[i]
                addi $t1, $t1, 4        # moving to next element address
                j loop1
        end1:

        # code to reset addresses for array
                addi $t1, $t0, 0        # &A[i]
        
        # code for reading in the user value X
                li $v0, 5               # system call code for read_int
                syscall                 # call read string
                add $t3, $v0, $zero     # store number in $t3 (power-of-two)
        
        # code for counting multiples of X in arrayA
                addi $t5, $t3, -1       # bitmask
        loop2:  bge $t1, $t2, end2
                lw $t4, 0($t1)          # $t4 is A[i]
                and $t6, $t4, $t5       # $t6 is remainder
                bne $t6, $zero, skip
                addi $s0, $s0, 1        # ans++
        skip:   addi $t1, $t1, 4        # moving to next element address
                j loop2
        end2:

        # code for printing result
                li $v0, 1               # system call code for print_int
                add $a0, $s0, $zero     # integer to print
                syscall                 # print the integer

        # code for terminating the program
        li $v0, 10
        syscall