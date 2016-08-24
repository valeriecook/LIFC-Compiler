.data
.text
    la $t1 0($sp)
    addiu $sp $sp -16
    sw $t1 0($sp)
    sw $ra 12($sp)
    sw $t0 8($sp)
    li $v0 5
    sw  $v0 4($sp)
    jal func_fib
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
func_fib:
    addiu $sp $sp -4
    sw $fp 0($sp)
    la $fp 4($sp)
    lw  $v0  4($fp)
    beq $v0 $0 anddone0
    lw  $v0  4($fp)
    move $t0 $v0
    li $v0 1
    sub $v0 $t0 $v0
    beq $v0 $0 anddone0
    li $v0 1
anddone0:
    beq $v0 $0 iffalse0
    la $t1 0($sp)
    addiu $sp $sp -16
    sw $t1 0($sp)
    sw $ra 12($sp)
    sw $t0 8($sp)
    lw  $v0  4($fp)
    move $t0 $v0
    li $v0 1
    sub $v0 $t0 $v0
    sw  $v0 4($sp)
    jal func_fib
    lw $sp 0($sp)
    lw $ra -4($sp)
    lw $t0 -8($sp)
    move $t0 $v0
    la $t1 0($sp)
    addiu $sp $sp -16
    sw $t1 0($sp)
    sw $ra 12($sp)
    sw $t0 8($sp)
    lw  $v0  4($fp)
    move $t0 $v0
    li $v0 2
    sub $v0 $t0 $v0
    sw  $v0 4($sp)
    jal func_fib
    lw $sp 0($sp)
    lw $ra -4($sp)
    lw $t0 -8($sp)
    add $v0 $v0 $t0
    j ifdone0
iffalse0:
    lw  $v0  4($fp)
ifdone0:
    lw $fp 0($sp)
    addiu $sp $sp 4
    jr $ra
