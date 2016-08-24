.data
str0:    .asciiz    "lalala"
x: .word 0
y: .word 0
.text
    li $v0 5
    sw $v0 x
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    la $v0 str0
    sw $v0 y
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
    li $v0 10
    syscall
