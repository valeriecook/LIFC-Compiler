.data
.text
    li $v0 0
    beq $v0 $0 anddone0
    li $v0 0
    beq $v0 $0 anddone0
    li $v0 1
anddone0:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    beq $v0 $0 anddone1
    li $v0 2
    beq $v0 $0 anddone1
    li $v0 1
anddone1:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 3
    beq $v0 $0 anddone2
    li $v0 0
    beq $v0 $0 anddone2
    li $v0 1
anddone2:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 4
    beq $v0 $0 anddone3
    li $v0 5
    beq $v0 $0 anddone3
    li $v0 1
anddone3:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    bne $v0 $0 ortrue0
    li $v0 0
    beq $v0 $0 ordone0
ortrue0:
    li $v0 1
ordone0:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    bne $v0 $0 ortrue1
    li $v0 2
    beq $v0 $0 ordone1
ortrue1:
    li $v0 1
ordone1:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 3
    bne $v0 $0 ortrue2
    li $v0 0
    beq $v0 $0 ordone2
ortrue2:
    li $v0 1
ordone2:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 4
    bne $v0 $0 ortrue3
    li $v0 5
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
