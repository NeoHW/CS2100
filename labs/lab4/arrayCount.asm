# arrayCount.asm
        .data
arrayA: .word 1, 0, 2, 0, 3 # arrayA has 5 values
count:  .word 999           # dummy value

        .text
main:
        # code to set up the variable mappings
        add $zero, $zero, $zero     # dummy instructions
                                    # can be removed
        # code for reading in the user value X
        # code for counting multiples of X in arrayA
        # code for printing result
        # code for terminating the program
        li $v0, 10
        system