.data
.text
    la $t1 0($sp)
    addiu $sp $sp -16
    sw $t1 0($sp)
    sw $ra 12($sp)
    sw $t0 8($sp)
    li $v0 1
    sw  $v0 4($sp)
    jal func_myfunc2
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
func_myfunc1:
    addiu $sp $sp -4
    sw $fp 0($sp)
    la $fp 4($sp)
    lw  $v0  8($fp)
    move $t0 $v0
    lw  $v0  4($fp)
    add $v0 $v0 $t0
    lw $fp 0($sp)
    addiu $sp $sp 4
    jr $ra
func_myfunc2:
    addiu $sp $sp -4
    sw $fp 0($sp)
    la $fp 4($sp)
    la $t1 0($sp)
    addiu $sp $sp -20
    sw $t1 0($sp)
    sw $ra 16($sp)
    sw $t0 12($sp)
    lw  $v0  4($fp)
    sw  $v0 8($sp)
    li $v0 4
    sw  $v0 4($sp)
    jal func_myfunc1
    lw $sp 0($sp)
    lw $ra -4($sp)
    lw $t0 -8($sp)
    lw $fp 0($sp)
    addiu $sp $sp 4
    jr $ra
