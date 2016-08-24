.data
str0:    .asciiz    "hi"
.text
    li $v0 2
    move $t0 $v0
    la $v0 str0
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
    add $v0 $v0 $t0
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
