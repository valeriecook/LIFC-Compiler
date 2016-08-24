.data
str0:    .asciiz    "A truly nasty example of scoping in LIFC."
str1:    .asciiz    "Credit for it goes to Ulysse Manceron."
mycode: .word 0
.text
    la $v0 str0
    la $v0 str1
    li $v0 21
    sw $v0 mycode
    la $t1 0($sp)
    addiu $sp $sp -16
    sw $t1 0($sp)
    sw $ra 12($sp)
    sw $t0 8($sp)
    lw $v0 mycode
    move $t0 $v0
    li $v0 2
    mult $v0 $t0
    mflo $v0
    sw  $v0 4($sp)
    jal func_mycode
    lw $sp 0($sp)
    lw $ra -4($sp)
    lw $t0 -8($sp)
    li $v0 10
    syscall
func_mycode:
    addiu $sp $sp -4
    sw $fp 0($sp)
    la $fp 4($sp)
    lw  $v0  4($fp)
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    lw $fp 0($sp)
    addiu $sp $sp 4
    jr $ra
