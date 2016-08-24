.data
.text
    li $v0 0
    move $t0 $v0
    li $v0 0
    slt $v0 $t0 $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    move $t0 $v0
    li $v0 2
    slt $v0 $t0 $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 3
    move $t0 $v0
    li $v0 0
    slt $v0 $t0 $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 -4
    move $t0 $v0
    li $v0 1
    slt $v0 $t0 $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    move $v1 $v0
    li $v0 0
    beq $v0 $v1 eqtrue0
    move $v0 $0
    j eqdone0
eqtrue0:
    li $v0 1
eqdone0:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 7
    move $v1 $v0
    li $v0 58
    beq $v0 $v1 eqtrue1
    move $v0 $0
    j eqdone1
eqtrue1:
    li $v0 1
eqdone1:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 -1
    move $v1 $v0
    li $v0 -1
    beq $v0 $v1 eqtrue2
    move $v0 $0
    j eqdone2
eqtrue2:
    li $v0 1
eqdone2:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
