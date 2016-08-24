.data
struct0:    .space  24
.text
    la $t0 struct0
    li $v0 0
    sw $v0 0($t0)
    li $v0 1
    sw $v0 4($t0)
    li $v0 2
    sw $v0 8($t0)
    li $v0 3
    sw $v0 12($t0)
    li $v0 4
    sw $v0 16($t0)
    li $v0 5
    sw $v0 20($t0)
    li $v0 1
    move $t0 $v0
    li $v0 2
    add $v0 $v0 $t0
   la $t0 struct0
    li $v1 4
    mult $v0 $v1
    mflo $v0
    add $t0 $t0 $v0
    lw $v0 0($t0)
    #print $v0
    move $a0 $v0
    li $v0 1
    syscall
    move $v0 $0
    li $v0 10
    syscall
