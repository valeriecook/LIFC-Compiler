.data
struct0:    .space  24
struct1:    .space  24
struct2:    .space  16
struct3:    .space  24
struct4:    .space  20
struct5:    .space  24
struct6:    .space  16
str0:    .asciiz    "hi"
str1:    .asciiz    "string"
str2:    .asciiz    "\n"
struct7:    .space  24
struct8:    .space  24
struct9:    .space  16
struct10:    .space  24
struct11:    .space  20
struct12:    .space  24
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
    li $v0 0
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
    la $t0 struct1
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
   la $t0 struct1
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
    la $t0 struct2
    li $v0 0
    sw $v0 0($t0)
    li $v0 1
    sw $v0 4($t0)
    li $v0 2
    sw $v0 8($t0)
    li $v0 3
    sw $v0 12($t0)
    li $v0 2
   la $t0 struct2
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
    la $t0 struct3
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
    li $v0 3
   la $t0 struct3
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
    la $t0 struct4
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
    li $v0 4
   la $t0 struct4
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
    la $t0 struct5
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
    li $v0 5
   la $t0 struct5
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
    la $t0 struct6
    li $v0 0
    sw $v0 0($t0)
    la $v0 str0
    sw $v0 4($t0)
    la $v0 str1
    sw $v0 8($t0)
    la $v0 str2
    sw $v0 12($t0)
    li $v0 3
   la $t0 struct6
    li $v1 4
    mult $v0 $v1
    mflo $v0
    add $t0 $t0 $v0
    lw $v0 0($t0)
    #print $v0
    move $a0 $v0
    li $v0 4
    syscall
    move $v0 $0
    la $t0 struct7
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
    li $v0 0
   la $t0 struct7
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
    la $t0 struct8
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
   la $t0 struct8
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
    la $t0 struct9
    li $v0 0
    sw $v0 0($t0)
    li $v0 1
    sw $v0 4($t0)
    li $v0 2
    sw $v0 8($t0)
    li $v0 3
    sw $v0 12($t0)
    li $v0 2
   la $t0 struct9
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
    la $t0 struct10
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
    li $v0 3
   la $t0 struct10
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
    la $t0 struct11
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
    li $v0 4
   la $t0 struct11
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
    la $t0 struct12
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
    li $v0 5
   la $t0 struct12
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
