.data
x: .word 0
.text
    li $v0 2
    sw $v0 x
whilestart0:
    lw $v0 x
    beq $v0 $0 whiledone0
    li $v0 0
    sw $v0 x
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    j whilestart0
whiledone0:
    move $v0 $0
    li $v0 10
    syscall
