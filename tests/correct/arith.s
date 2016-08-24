.data
.text
    li $v0 3
    move $t0 $v0
    li $v0 6
    add $v0 $v0 $t0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 3
    move $t0 $v0
    li $v0 6
    sub $v0 $t0 $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 6
    move $t0 $v0
    li $v0 3
    div $t0 $v0
    mflo $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 3
    move $t0 $v0
    li $v0 6
    mult $v0 $t0
    mflo $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
