.data
.text
    li $v0 1
    bne $v0 $0 ortrue0
    li $v0 1
    beq $v0 $0 ordone0
ortrue0:
    li $v0 1
ordone0:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 1
    bne $v0 $0 ortrue1
    li $v0 0
    beq $v0 $0 ordone1
ortrue1:
    li $v0 1
ordone1:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    bne $v0 $0 ortrue2
    li $v0 1
    beq $v0 $0 ordone2
ortrue2:
    li $v0 1
ordone2:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    bne $v0 $0 ortrue3
    li $v0 0
    beq $v0 $0 ordone3
ortrue3:
    li $v0 1
ordone3:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
