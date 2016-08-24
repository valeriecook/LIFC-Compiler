.data
.text
    li $v0 9
    move $v1 $v0
    li $v0 -3228
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
    li $v0 0
    move $v1 $v0
    li $v0 0
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
    li $v0 10
    syscall
