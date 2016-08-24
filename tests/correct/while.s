.data
str0:    .asciiz    "\n"
x: .word 0
.text
    li $v0 10
    sw $v0 x
whilestart0:
    lw $v0 x
    move $t0 $v0
    li $v0 1
    sub $v0 $t0 $v0
    sw $v0 x
    beq $v0 $0 whiledone0
    lw $v0 x
    move $t0 $v0
    la $v0 str0
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
    add $v0 $v0 $t0
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
