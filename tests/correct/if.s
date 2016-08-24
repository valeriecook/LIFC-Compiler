.data
str0:    .asciiz    "success\n"
str1:    .asciiz    "fail\n"
str2:    .asciiz    "fail\n"
str3:    .asciiz    "success\n"
.text
    li $v0 1
    beq $v0 $0 iffalse0
    la $v0 str0
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
    j ifdone0
iffalse0:
    la $v0 str1
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
ifdone0:
    li $v0 0
    beq $v0 $0 iffalse1
    la $v0 str2
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
    j ifdone1
iffalse1:
    la $v0 str3
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
ifdone1:
    li $v0 10
    syscall
