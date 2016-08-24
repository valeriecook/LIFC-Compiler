.data
x: .word 0
y: .word 0
.text
    li $v0 5
    sw $v0 x
    lw $v0 x
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    lw $v0 x
    move $t0 $v0
    li $v0 1
    add $v0 $v0 $t0
    sw $v0 x
    sw $v0 y
    lw $v0 x
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    lw $v0 y
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
