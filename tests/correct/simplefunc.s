.data
.text
    la $t1 0($sp)
    addiu $sp $sp -16
    sw $t1 0($sp)
    sw $ra 12($sp)
    sw $t0 8($sp)
    li $v0 3
    sw  $v0 4($sp)
    jal func_add1
    lw $sp 0($sp)
    lw $ra -4($sp)
    lw $t0 -8($sp)
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
func_add1:
    addiu $sp $sp -4
    sw $fp 0($sp)
    la $fp 4($sp)
    lw  $v0  4($fp)
    move $t0 $v0
    li $v0 1
    add $v0 $v0 $t0
    lw $fp 0($sp)
    addiu $sp $sp 4
    jr $ra
