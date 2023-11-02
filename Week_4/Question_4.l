%{
#include <stdio.h>

/* Define a symbol table to store identifiers */
#define MAX_IDENT_LENGTH 64
char symbol_table[100][MAX_IDENT_LENGTH];
int symbol_count = 0;
%}

%option noyywrap

/* Regular expressions for tokens */
%%
"if"                { printf("IF\n"); }
"else"              { printf("ELSE\n"); }
"while"             { printf("WHILE\n"); }
"for"               { printf("FOR\n"); }
"int"               { printf("INT\n"); }
"float"             { printf("FLOAT\n"); }
"return"            { printf("RETURN\n"); }
"break"             { printf("BREAK\n"); }
"continue"          { printf("CONTINUE\n"); }
"main"              { printf("MAIN\n"); }
[a-zA-Z_][a-zA-Z0-9_]*   {
    /* Check if the identifier is already in the symbol table */
    int i;
    for (i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], yytext) == 0) {
            break;  /* Identifier already in the symbol table */
        }
    }
    
    if (i == symbol_count) {
        /* Identifier is not in the symbol table, add it */
        strcpy(symbol_table[symbol_count], yytext);
        printf("IDENTIFIER %s\n", yytext);
        symbol_count++;
    }
}

[0-9]+              { printf("INTEGER %s\n", yytext); }
"<"                 { printf("LESS_THAN\n"); }
">"                 { printf("GREATER_THAN\n"); }
"<="                { printf("LESS_THAN_OR_EQUAL\n"); }
">="                { printf("GREATER_THAN_OR_EQUAL\n"); }
"=="                { printf("EQUALS\n"); }
"!="                { printf("NOT_EQUALS\n"); }
"/*"                { /* Multi-line comment found, enter comment mode */
                    while (1) {
                        char c = input();
                        if (c == '*') {
                            char next = input();
                            if (next == '/') {
                                break;  /* End of comment */
                            }
                        }
                    }
                  }
.                   { /* Ignore any other characters */}
%%

int input() {
    return fgetc(yyin);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    
    if (yyin == NULL) {
        perror("Error opening input file");
        return 1;
    }
    
    yylex();
    
    fclose(yyin);
    
    return 0;
}
