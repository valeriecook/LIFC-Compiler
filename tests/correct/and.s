.data
n: .word 0
.text
    li $v0 1
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
    li $v0 0
    beq $v0 $0 anddone1
    li $v0 1
anddone1:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 0
    beq $v0 $0 anddone2
    li $v0 1
    beq $v0 $0 anddone2
    li $v0 1
anddone2:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 1
    beq $v0 $0 anddone3
    li $v0 1
    beq $v0 $0 anddone3
    li $v0 1
anddone3:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 3
    sw $v0 n
    lw $v0 n
    beq $v0 $0 anddone4
    lw $v0 n
    move $t0 $v0
    li $v0 1
    sub $v0 $t0 $v0
    beq $v0 $0 anddone4
    li $v0 1
anddone4:
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
