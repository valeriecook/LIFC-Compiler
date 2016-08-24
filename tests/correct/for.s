.data
i: .word 0
.text
    li $v0 0
    sw $v0 i
    li $v0 0
forstart0:
    lw $v0 i
    move $t0 $v0
    li $v0 10
    slt $v0 $t0 $v0
    beq $v0 $0 fordone0
    lw $v0 i
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    lw $v0 i
    move $t0 $v0
    li $v0 1
    add $v0 $v0 $t0
    sw $v0 i
    j forstart0
fordone0:
    move $v0 $0
    li $v0 10
    syscall
