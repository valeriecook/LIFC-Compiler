.data
.text
    li $v0 5
    move $t0 $v0
    li $v0 1
    add $v0 $v0 $t0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
