#include "code_gen.h"
#include "parser.h"

/** A counter to prevent the issuance of duplicate labels. */
unsigned label_count = 0;
/** True iff the data segment has already been partially printed. */
int data_seg_opened = 0;
/** True iff the text segment has already been partially printed. */
int text_seg_opened = 0;
int data_str_num = 0;
int data_struct_num = 0;

int and_counter = 0;
int or_counter = 0;
int eq_counter = 0;
int if_counter = 0;
int while_counter = 0;
int for_counter = 0;
void emit_strings(AST *ast) {
    /* TODO: Implement me. */
    
    if (data_seg_opened == 0) {
	printf(".data\n");
	data_seg_opened = 1;
    }
    if (ast) {
	if (ast->type == node_STRING) {
	    // add string to data
	    printf("str%d:    .asciiz    \"%s\"\n", data_str_num, ast->val);
	    
	    ast->label_num = data_str_num;
	    data_str_num++;
	}
	if (ast->type == node_STRUCT) {
	    // get number of children
	    AST_lst *next_child = ast->children;
	    int num_children = 0;
	    while (next_child != NULL) {
		num_children++;
		next_child = next_child->next;
	    }
	    // add struct to data
	    printf("struct%d:    .space  %d\n", data_struct_num, (num_children * 4));
	    ast->label_num = data_struct_num;
	    data_struct_num++;
	}
	AST_lst *next_child = ast->children;
	while (next_child != NULL) {
	    emit_strings(next_child->val);
	    next_child = next_child->next;
	}
    }
}

void emit_static_memory() {
    /* TODO: Implement me. */
    if (data_seg_opened == 0) {
	printf(".data\n");
	data_seg_opened = 1;
    }
    for (int i = 0; i < smap_num_pairs(decls); i++) {
	printf("%s: .word 0\n", smap_get_key(decls, i));
    }
}

void emit_main(AST *ast) {
    /* TODO: Implement me. */
    if (text_seg_opened == 0) {
	printf(".text\n");
	text_seg_opened = 1;
    }
    
    if (ast->type != node_FUNCTION) {
	emit_code(ast, NULL);
    }
}

void emit_code(AST *ast, smap *locals) {
    int label_number = 0;
    int offset = 0;
    AST_lst * next_child;
    
    switch (ast->type) {
    case node_S_PRINT:
    	emit_code(ast->children->val, locals);
    	printf("    #print $v0\n");
    	printf("    move $a0 $v0\n");
    	printf("    li $v0 4\n");
    	printf("    syscall\n");
	printf("    move $v0 $0\n");
    	break;
    case node_I_PRINT:
        emit_code(ast->children->val, locals);
   	printf("    #print $v0\n");
  	printf("    move $a0 $v0\n");
    	printf("    li $v0 1\n");
    	printf("    syscall\n");
	printf("    move $v0 $0\n");
    	break;
    case node_INT:
      	printf("    li $v0 %s\n", ast->val);
      	break;
    case node_STRING:
	printf("    la $v0 str%d\n", ast->label_num);
	break;
    case node_STRUCT:
	offset = 0;
	if (ast->children) {
	    printf("    la $t0 struct%d\n", ast->label_num);
	    AST_lst *next_child = ast->children;
	    while (next_child != NULL) {
		emit_code(next_child->val, locals);
		printf("    sw $v0 %d($t0)\n", offset);
		offset += 4;
		next_child = next_child->next;
	    }
	}
	break;
    case node_ARROW:
	emit_code(ast->children->val, locals);
	emit_code(ast->last_child->val, locals);
      	printf("   la $t0 struct%d\n", ast->children->val->label_num);
	printf("    li $v1 4\n");   
	printf("    mult $v0 $v1\n");
	printf("    mflo $v0\n");
	printf("    add $t0 $t0 $v0\n");
	printf("    lw $v0 0($t0)\n");
	break;
    case node_PLUS:
	emit_code(ast->children->val, locals);
	printf("    move $t0 $v0\n");
	emit_code(ast->children->next->val, locals);
	printf("    add $v0 $v0 $t0\n");
	break;
    case node_MINUS:
	emit_code(ast->children->val, locals);
	printf("    move $t0 $v0\n");
	emit_code(ast->children->next->val, locals);
	printf("    sub $v0 $t0 $v0\n");
	break;
    case node_MUL:
	emit_code(ast->children->val, locals);
	printf("    move $t0 $v0\n");
	emit_code(ast->children->next->val, locals);
      	printf("    mult $v0 $t0\n");
	printf("    mflo $v0\n");
	break;
    case node_DIV:
	emit_code(ast->children->val, locals);
	printf("    move $t0 $v0\n");
	emit_code(ast->children->next->val, locals);
	printf("    div $t0 $v0\n");
	printf("    mflo $v0\n");
	break;
    case node_AND:
	emit_code(ast->children->val, locals);
	label_number = and_counter;
	and_counter++;
	printf("    beq $v0 $0 anddone%d\n", label_number);
        emit_code(ast->children->next->val, locals);
        printf("    beq $v0 $0 anddone%d\n", label_number);
        printf("    li $v0 1\n");
        printf("anddone%d:\n", label_number);
	break;
    case node_OR:
	emit_code(ast->children->val, locals);
	label_number = or_counter;
	or_counter++;
	printf("    bne $v0 $0 ortrue%d\n", label_number);
	emit_main(ast->children->next->val);
	printf("    beq $v0 $0 ordone%d\n", label_number);
	printf("ortrue%d:\n", label_number);
	printf("    li $v0 1\n");
	printf("ordone%d:\n", label_number);
	break;
    case node_LT:
	emit_code(ast->children->val, locals);
	printf("    move $t0 $v0\n");
	emit_code(ast->children->next->val, locals);
	printf("    slt $v0 $t0 $v0\n");
	break;
    case node_EQ:
	emit_code(ast->children->val, locals);
	label_number = eq_counter;
	eq_counter++;
	printf("    move $v1 $v0\n");
	emit_code(ast->children->next->val, locals);
	printf("    beq $v0 $v1 eqtrue%d\n", label_number);
	printf("    move $v0 $0\n");
	printf("    j eqdone%d\n", label_number);
	printf("eqtrue%d:\n", label_number);
	printf("    li $v0 1\n");
	printf("eqdone%d:\n", label_number);
	break;
    case node_IF:
	label_number = if_counter;
	if_counter++;
	emit_code(ast->children->val, locals);
	printf("    beq $v0 $0 iffalse%d\n", label_number);
	emit_code(ast->children->next->val, locals);
	printf("    j ifdone%d\n", label_number);
	printf("iffalse%d:\n", label_number);
	emit_code(ast->last_child->val, locals);
	printf("ifdone%d:\n", label_number);
	break;
    case node_READ_INT:
	printf("    li $v0 5\n");
	printf("    syscall\n");
	break;
    case node_SEQ:
	next_child = ast->children;
	while (next_child != NULL) {
	    emit_code(next_child->val, locals);
      	    next_child = next_child->next;
	}
	break;
    case node_WHILE:
	label_number = while_counter;
	while_counter++;
	printf("whilestart%d:\n", label_number);
	emit_code(ast->children->val, locals);
	printf("    beq $v0 $0 whiledone%d\n", label_number);
	emit_code(ast->children->next->val, locals);
	printf("    j whilestart%d\n", label_number);
	printf("whiledone%d:\n", label_number);
	printf("    move $v0 $0\n");
	break;
    case node_FOR:
	label_number = for_counter;
	for_counter++;
	emit_code(ast->children->val, locals);
	printf("forstart%d:\n", label_number);
	emit_code(ast->children->next->val, locals);
	printf("    beq $v0 $0 fordone%d\n", label_number);
	emit_code(ast->last_child->val, locals);
	emit_code(ast->children->next->next->val, locals);
	printf("    j forstart%d\n", label_number);
	printf("fordone%d:\n", label_number);
	printf("    move $v0 $0\n");
	break;

    case node_CALL:
	// Save space for registers and args
	offset = ((smap_get(function_list, ast->val) + 3) * -4);
	printf("    la $t1 0($sp)\n");
	printf("    addiu $sp $sp %d\n", offset);
	printf("    sw $t1 0($sp)\n");
	
	// Save registers that might be clobbered
	offset = (offset * -1) - 4;
	printf("    sw $ra %d($sp)\n", offset);
	offset -= 4;
	printf("    sw $t0 %d($sp)\n", offset);
       
	// Push args
	next_child = ast->children;
	while (next_child != NULL) {
	    offset -= 4;
	    emit_code(next_child->val, locals);
	    printf("    sw  $v0 %d($sp)\n", offset);
     	    next_child = next_child->next;
	}
	
	// Call the function
	printf("    jal func_%s\n", ast->val);
	
	// Clean up args
	printf("    lw $sp 0($sp)\n");
	
	// Restore registers we saved
	printf("    lw $ra -4($sp)\n");
	printf("    lw $t0 -8($sp)\n");
	
	break;
    case node_VAR:
	// Is it a local var?
	offset = smap_get(locals, ast->val);

	if (offset == -1) {

	    // Must be global var
	    printf("    lw $v0 %s\n", ast->val);

	} else {
	    
	    printf("    lw  $v0  %d($fp)\n", offset); 
	}
	break;
    case node_ASSIGN:
	// Is it a local var?
	offset = smap_get(locals, ast->children->val->val);

	// The value to be assigned
	emit_code(ast->children->next->val, locals);

	// If it is an assignment to a new local var
	if ( offset == -1 && (smap_get(decls, ast->children->val->val) == -1)) {
	    // Add to locals and change offset and push on to the stack
	    int num_pairs = smap_num_pairs(locals);
	    for (int i = 0; i < num_pairs; i++) {
		smap_increment(locals, smap_get_key(locals, i), 4);
	    }
	    char *var = safe_calloc((strlen(ast->children->val->val) + 1) * sizeof(char));
	    strncpy(var, ast->children->val->val, strlen(ast->children->val->val));
	    smap_put(locals, var, 4);
	    printf("    lw $t0 0($sp)\n");
	    printf("    sw $v0 0($sp)\n");
	    printf("    addiu $sp $sp -4\n");
	    printf("    sw $t0 0($sp)\n");
	} else {
	
	// If it is a global var
	    if (offset == -1) {
		printf("    sw $v0 %s\n", ast->children->val->val);
	    } else { // It is a local var that has already been defined
		printf("    sw $v0 %d($sp)\n", offset);
	    }
	}
	break;
    default:
    	break;
    }
}

void emit_exit() {
    printf("    li $v0 10\n");
    printf("    syscall\n");
}

void emit_functions(AST *ast) {
    /* TODO: Implement me. */
    if (ast->type == node_FUNCTION) {

	// Make smap for offsets
	smap *locals = smap_new();
	int num_args = lookup_function(ast->val);

	AST_lst *next_child = ast->children;
	while (next_child != ast->last_child) {
	    char *var = safe_calloc((strlen(next_child->val->val) + 1) * sizeof(char));
	    strncpy(var, next_child->val->val, strlen(next_child->val->val));
	    smap_put(locals, var, (num_args * 4));
	    num_args--;
	    next_child = next_child->next;
	}
	
	// Emit the code  (we will add new loc vars when assign statements are found)
       	printf("func_%s:\n", ast->val);
	printf("    addiu $sp $sp -4\n");
	printf("    sw $fp 0($sp)\n");
	printf("    la $fp 4($sp)\n");
       	emit_code(ast->last_child->val, locals);
	printf("    lw $fp 0($sp)\n");
	printf("    addiu $sp $sp 4\n");

	// Return to caller
	printf("    jr $ra\n");

	smap_del_contents(locals);
	smap_del(locals);
    }
}
