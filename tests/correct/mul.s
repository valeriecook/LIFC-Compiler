.data
.text
    li $v0 2
    move $t0 $v0
    li $v0 4
    mult $v0 $t0
    mflo $v0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
