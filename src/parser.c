#include "parser.h"
#include "lexer.h"
#include <string.h>
#include <stdlib.h>

/** An array of the different string values of keywords. */
char *keywords[] = {"and", "or", "+", "-", "*", "/", "lt", "eq", 
		    "function", "struct", "arrow", "assign", "if", 
		    "while", "for", "sequence", "intprint", "stringprint",
		    "readint"};
/** Sister array of keywords. Keeps track of the corresponding enum. */
int enums[] = {node_AND, node_OR, node_PLUS, node_MINUS, node_MUL, node_DIV,
	       node_LT, node_EQ, node_FUNCTION, node_STRUCT, 
	       node_ARROW, node_ASSIGN, node_IF, node_WHILE, node_FOR, 
	       node_SEQ, node_I_PRINT, node_S_PRINT, node_READ_INT};
/** A hashmap used for more efficient lookups of (keyword, enum) pairs. */
smap *keyword_str_to_enum;


/** Initializes keyword_str_to_enum so that it contains a map
 *  from the string value of a keyword to its corresponding enum. */
void initialize_keyword_to_enum_mapping();

int building_function = 0;
int declsnotallowed = 0;

void parse_init() {
    decls = smap_new();
    stack_sizes = smap_new();
    num_args = smap_new();
    strings = smap_new();
    keyword_str_to_enum = smap_new();
    function_list = smap_new();
    local_decls = smap_new();
    
}

void parse_close() {
    smap_del_contents(decls);
    smap_del(decls);
    smap_del(stack_sizes);
    smap_del(num_args);
    smap_del(strings);
    smap_del(keyword_str_to_enum);
    smap_del(function_list);
    smap_del_contents(local_decls);
    smap_del(local_decls);
}

AST *build_ast (lexer *lex) {
    /* TODO: Implement me. */
    /* Hint: switch statements are pretty cool, and they work 
     *       brilliantly with enums. */

    AST *ast = add_expression(NULL, lex);
    return ast;
}

AST *add_expression(AST *ast, lexer *lex) {
    AST *node = NULL;
    
    switch (lex->type) {
    case token_OPEN_PAREN:
	node = add_paren_expression(ast, lex);
	break;
    default:
	node = add_atom(ast, lex);
	if (node->type == node_VAR) {
	    if (ast->type != node_ASSIGN) {
		if (smap_get(decls, node->val) == -1) {
		    if ( !building_function || (smap_get(local_decls, node->val) == -1)) {
		    	fatal_error("Variables must be assigned before they are used\n");
		    }
		}
	    }
	}
	break;
    }
    return node;
}

AST *add_paren_expression(AST *ast, lexer *lex) {
    // Add operator
    read_token(lex); 
    AST *node = add_atom(ast, lex);
    int done = 0;
    
    // Check if operator is function
    if (node->type == node_FUNCTION) {
	if (ast){
	    fatal_error("Function can only be defined at top-level\n");
	}
	building_function = 1;
	add_function_expression(node, lex);
	building_function = 0;
	done = 1;
    }
    
    // Check if operator should be a function call
    if (node->type == node_VAR) {
	if (lookup_function(node->val) == -1) {
	    fatal_error("Functions must be defined before you can call them\n");
	}
	node->type = node_CALL;     
    }

    // Check if var has already been assigned
    if (node->type == node_ASSIGN) {
	if (lex->type != token_NAME) {
	    fatal_error("Assign must be followed by a variable\n");
	}
        if (smap_get(decls, lex->buffer) == -1) {
	    if (!building_function) {
		char *varname = safe_calloc((lex->buff_len + 1) * sizeof(char));
		strncpy(varname, lex->buffer, lex->buff_len);
		smap_put(decls, varname, 0);
		strcpy(node->val, "1") ; // Mark as a definition
 	    } else {
		if (smap_get(local_decls, lex->buffer) == -1) {
		    char *varname = safe_calloc((lex->buff_len + 1) * sizeof(char));
		    strncpy(varname, lex->buffer, lex->buff_len);
		    smap_put(local_decls, varname, 0);
		    strcpy(node->val, "1"); // Mark as a definition 
		}
	    }
	}
    }

    // Add operands
    while (!done){
	switch (lex->type) {
	case token_CLOSE_PAREN:
	    read_token(lex);
	    done = 1;
	    break;
	case token_END:
	case token_SENTINEL:
	    fatal_error( "Invalid paren expression\n");
	default:
	    add_expression(node, lex);
	}
    }
    return node;
}

void add_function_expression(AST *ast, lexer *lex) {
    int done = 0;
    int num_args = 0;
    AST *node = NULL;
    
    // Confirm open paren
    if (lex->type != token_OPEN_PAREN) {
	fatal_error("Invalid function def");
    }
    
    // Read function name
    read_token(lex);
    if (lex->type != token_NAME) {
	fatal_error("Invalid function name");
    }
    if (lookup_function(lex->buffer) != -1) {
	fatal_error("Function has already been defined");
    }
    
    // Replace ast->val with function name
    free(ast->val);
    ast->val = safe_calloc((lex->buff_len + 1) * sizeof(char));
    strncpy(ast->val, lex->buffer, lex->buff_len);
    
    // Read args of function
    smap_del_contents(local_decls);
    read_token(lex);
    while (!done) {
	switch (lex->type) {
	case token_CLOSE_PAREN:
	    read_token(lex);
	    done = 1;
	    break;
	case token_NAME:
	    node = add_atom(ast, lex);
	    if (smap_get(local_decls, node->val) == -1) {
		char *localvar = safe_calloc((strlen(node->val) + 1) * sizeof(char));
		strncpy(localvar, node->val, strlen(node->val));
		smap_put(local_decls, localvar, 0);
	    } else {
		fatal_error("Duplicate argument name\n");
	    }
	    num_args++;
	    break;
	default:
	    fatal_error("Function args must be names\n");
	}
    }
    
    smap_put(function_list, ast->val, num_args);
    
    // Read function body
    add_expression(ast, lex);

    // Read close paren
    if (lex->type != token_CLOSE_PAREN) {
	fatal_error("Missing close paren for function def\n");
    }
    read_token(lex);
}

int lookup_function(char *function_name) {
    // Returns -1 if function name isn't found
    return smap_get(function_list, function_name);
}
    
void add_child(AST *ast, AST *node) {
    AST_lst *next_child = safe_calloc(sizeof(AST_lst));
    next_child->val = node;
    if (ast->children == NULL) {
	ast->children = next_child;
	ast->last_child = next_child;
    } else {
	ast->last_child->next = next_child;
	ast->last_child = next_child;
    }
}

AST *add_atom(AST *ast, lexer *lex) {
    AST *node = NULL;
    node = safe_calloc(sizeof(AST));
    node->val = safe_calloc((lex->buff_len + 1) * sizeof(char));
    strncpy(node->val, lex->buffer, lex->buff_len);
  
    switch(lex->type) {
    case token_INT:
	node->type = node_INT;
	break;
    case token_STRING:
	node->type = node_STRING;
	break;
    case token_NAME:
	node->type = node_VAR;
	break;
    case token_KEYWORD:
        node->type = lookup_keyword_enum(lex->buffer);
       	break;
    case token_END:
	free_ast(node);
	node = NULL;
	break;

     //WARNING ERROR
    default:
	free_ast(node);
	node = NULL;
	fprintf(stderr, "Invalid atom:type=%d buffer=%s \n", lex->type, lex->buffer);
	exit(1);
	break;
    }
    
    if(ast != NULL) {
	add_child(ast, node);
    }
    read_token(lex);		
    return node;
}

void free_ast (AST *ptr) {
    /* TODO: Implement me. */
    if (ptr) {
	if (ptr->val) {
	    free(ptr->val);
	    ptr->val = NULL;
	}
	free_ast_lst(ptr->children);
	free(ptr);
	ptr = NULL;
    }
}

void free_ast_lst (AST_lst *ptr){
    if (ptr) {
	if (ptr->val) {
	    free_ast(ptr->val);
	}
	if (ptr->next) {
	    free_ast_lst(ptr->next);
	}
	free(ptr);
	ptr = NULL;
    }
}

void check_tree_shape(AST *ptr) {
    /* TODO: Implement me. */
    /* Hint: This function is just asking to be table-driven */

    int expected = expected_num_args(ptr->type);

     // Get the number of children of the node
    int num_children = 0;
    if (ptr->children != NULL) {
	AST_lst *next_child = ptr->children;
	while (next_child != NULL) {
	    if ( (ptr->type == node_IF) && (next_child != ptr->children) ) {
		declsnotallowed++;
		check_tree_shape(next_child->val);
		declsnotallowed--;
	    } else if ((ptr->type == node_WHILE) && (next_child != ptr->children)) {
		declsnotallowed++;
		check_tree_shape(next_child->val);
		declsnotallowed--;
	    } else if ((ptr->type == node_FOR) && ((next_child != ptr->children) || (ptr->children->next))) {
		declsnotallowed++;
		check_tree_shape(next_child->val);
		declsnotallowed--;
	    } else if (((ptr->type == node_AND) || (ptr->type == node_OR)) && (next_child != ptr->children)) {
		declsnotallowed++;
		check_tree_shape(next_child->val);
		declsnotallowed--;
	    } else {
		check_tree_shape(next_child->val);
	    }
	    num_children++;
	    next_child = next_child->next;
	}
    }

    if (expected == -1) {
	if (ptr->type == node_SEQ && num_children < 1) {
	     fatal_error("Incorrect number of arguments\n");
	}
	if (ptr->type == node_CALL) {
	    if (num_children != smap_get(function_list, ptr->val)) {
		fprintf(stderr, "Incorrect number of arguments in call to %s\n", ptr->val);
		exit(1);
	    }
	}
	return;
    }

    // Check that the number of arguments given equals  the required number  
    if (expected != num_children) {
	fprintf(stderr, "Incorrect number of arguments in type %d\n", ptr->type);
	exit(1);
    }

    if ((ptr->type == node_ASSIGN) && (declsnotallowed) && (strcmp(ptr->val, "1") == 0)) {
	fatal_error("Cannot declare vars in conditional clauses\n");
    }

    // Check that new declaration is not used in the assignment
    if ((ptr->type == node_ASSIGN) && (strcmp(ptr->val, "1") == 0)) {
	check_tree_for_val(ptr->children->next->val, ptr->children->val->val);
    }
	

}

void check_tree_for_val(AST *ast, char *var) {
    if (ast->val) {
	if (strcmp(ast->val, var) == 0) {
	    fatal_error("Cannot use variable in definition\n");
	}
    }
    if (ast->children != NULL) {
	AST_lst *next_child = ast->children;
	while (next_child != NULL) {
	    check_tree_for_val(next_child->val, var);
	    next_child = next_child->next;
	}
    }
}

int expected_num_args (node_type type) {
    
    switch (type) {
    case node_AND:
    case node_OR:
    case node_PLUS:
    case node_MINUS:
    case node_MUL:
    case node_LT:
    case node_EQ:
    case node_DIV:
    case node_ARROW:
    case node_ASSIGN:
    case node_WHILE:
	return 2;
    case node_IF:
	return 3;
    case node_FOR:
	return 4;
    case node_I_PRINT:
    case node_S_PRINT:
	return 1;
    case node_READ_INT:
	return 0;
    default:
	return -1;
    }
}

void gather_decls(AST *ast, char *env, int is_top_level) {
    /* TODO: Implement me. */
    /* Hint: switch statements are pretty cool, and they work 
     *       brilliantly with enums. */
}

node_type lookup_keyword_enum(char *str) {
    if (smap_get(keyword_str_to_enum, keywords[0]) == -1) {
	initialize_keyword_to_enum_mapping();
    }
    return smap_get(keyword_str_to_enum, str);
}

void initialize_keyword_to_enum_mapping() {
    /* Note that enums is an *array*, not a pointer, so this
     * sizeof business is reasonable. */
    size_t num_keywords = sizeof(enums) / sizeof(int);
    for (size_t i = 0; i < num_keywords; i += 1) {
	smap_put(keyword_str_to_enum, keywords[i], enums[i]);
    }
}

size_t AST_lst_len(AST_lst *lst) {
    int num_fields = 0;
    while (lst) {
	num_fields += 1;
	lst = lst->next;
    }
    return num_fields;
}


smap *decls;
smap *stack_sizes;
smap *num_args;
smap *strings;
smap *function_list;
smap *local_decls;
