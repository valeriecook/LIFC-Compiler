.data
.text
    li $v0 5
    move $t0 $v0
    li $v0 -8
    add $v0 $v0 $t0
    li $v0 10
    syscall
