#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include "util/util.h"
#include "parser.h"

void init_lex(lexer *luthor) {
    luthor->file = NULL;
    luthor->buffer = NULL;
    luthor->type = token_SENTINEL;
    luthor->buff_len = 0;
}

void open_file(lexer *lex, char *filename) {
    if (lex) {
	lex->file = fopen(filename, "r");
	if (!lex->file) {
      	    printf("%s\n", filename);
	    fatal_error("Could not read input file.\n");
	}
	lex->buff_len = INIT_BUFFER_SIZE;
	lex->buffer = safe_calloc(INIT_BUFFER_SIZE * sizeof(char));
    }
}

void close_file(lexer *lex) {
    if (lex) {
	fclose(lex->file);
	free(lex->buffer);
	lex->buff_len = 0;
	lex->buffer = NULL;
    }
}

void read_token(lexer *lex) {
    /* TODO: Implement me. */
    /* HINT: fgetc() and ungetc() could be pretty useful here. */
    int c  = fgetc(lex->file);
    char str[INIT_BUFFER_SIZE];
    char str1[INIT_BUFFER_SIZE];
    char str2[INIT_BUFFER_SIZE];
    int intres;
    int nameres;
    
   // Ignore whitespace
    while (isspace(c) && (c != EOF)) {
	c = fgetc(lex->file);
    }
    
    switch (c) {
    case EOF:
	lex->type = token_END;
	//	lex->buffer = "EOF";
	//	lex->buff_len = strlen("EOF");
	break;
    case '(':
        lex->type = token_OPEN_PAREN;
	//	lex->buffer = "(";
	//	lex->buff_len = strlen("(");
	break;
    case ')':
	lex->type = token_CLOSE_PAREN;
	//	lex->buffer = ")";
	//	lex->buff_len = strlen(")");
	break;
    case '"':
	fscanf(lex->file, "%[^\"]\"", str);
	lex->type = token_STRING;
	strncpy(lex->buffer, str, INIT_BUFFER_SIZE);
	lex->buff_len = strlen(str);
	break;
    default:
      	ungetc(c,lex->file);
	
	// Scan until whitespace or closing paren is found
	fscanf(lex->file, "%[^) \t\r\n\v\f]", str);

        // Is it a keyword?
	if (lookup_keyword_enum(str) != -1){
	    lex->type = token_KEYWORD;
	    strncpy(lex->buffer, str, INIT_BUFFER_SIZE);
	    lex->buff_len = strlen(str);
	    break;
	}
	
	// Is it a pos int?
        intres = sscanf(str, "%[0-9]",str1);
	if (intres !=0 && (strlen(str1) == strlen(str))) {
	    lex->type = token_INT;
	    lex->buff_len =  sprintf(lex->buffer, "%s", str1);
      	    break;
	}

	// Is it a neg int?
	if (c == '-') {
	    intres = sscanf(str, "%*c%[0-9]", str1);
	    if (intres != 0 && (strlen(str) == (strlen(str1) + 1))) {
		lex->type = token_INT;
		lex->buff_len =  sprintf(lex->buffer, "%s", str);
		break;	
	    } else {
		fprintf(stderr, "Invalid negative number: %s \n", str);
	    exit(1);
	    }
	}

	// Is it None?
	if (strcmp(str, "None") == 0) {
	    lex->type = token_INT;
	    lex->buff_len = sprintf(lex->buffer, "0");
	    break;
	}
	
	// Is it a name?
	nameres = sscanf(str, "%[a-zA-Z]%[a-zA-Z0-9]", str1, str2);
	if (nameres == 2) {
	    strcat(str1, str2);
	}
	if (nameres != 0 && (strlen(str1) == strlen(str))) {
       	    lex->type = token_NAME;
	    lex->buff_len =  sprintf(lex->buffer, "%s", str1);
	    break;
	}
	
	// Invalid input
	fprintf(stderr, "Invalid input: %s \n", str);
	exit(1);
    }
}

token_type peek_type(lexer *lex) {
    if (!lex) {
	return token_SENTINEL;
    }
    if (lex->type == token_SENTINEL) {
	read_token(lex);
    }
    return lex->type;
}

char *peek_value(lexer *lex) {
    if (!lex) {
	return NULL;
    }
    if (lex->type == token_SENTINEL) {
	read_token(lex);
    }
    return lex->buffer;
}
