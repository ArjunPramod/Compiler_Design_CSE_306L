%{
#include <stdio.h>
%}

/* Regular Expressions for Tokens */
digit           [0-9]
letter          [a-zA-Z]
identifier      {letter}({letter}|{digit})*
constant        {digit}+
comment          "/*"([^*]|"*"[^/])*"*/"
whitespace      [ \t\n]+

%%
/* Rules to recognize and process tokens */
{whitespace}    /* Ignore whitespace, tabs, and newlines */

{comment}       /* Ignore comments */

int             { return INT; }
{identifier}    { yylval.str = strdup(yytext); return IDENTIFIER; }
{constant}      { yylval.str = strdup(yytext); return CONSTANT; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"="             { return ASSIGN; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
";"             { return SEMICOLON; }
"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"endif"         { return ENDIF; }
"while"         { return WHILE; }
"do"            { return DO; }
"enddo"         { return ENDDO; }
"print"         { return PRINT; }

%%
int main() {
    int token;
    while ((token = yylex()) != 0) {
        switch (token) {
            case INT:
                printf("Token: INT\n");
                break;
            case IDENTIFIER:
                printf("Token: IDENTIFIER, Value: %s\n", yylval.str);
                free(yylval.str);
                break;
            case CONSTANT:
                printf("Token: CONSTANT, Value: %s\n", yylval.str);
                free(yylval.str);
                break;
            case PLUS:
                printf("Token: PLUS\n");
                break;
            case MINUS:
                printf("Token: MINUS\n");
                break;
            case MULTIPLY:
                printf("Token: MULTIPLY\n");
                break;
            case DIVIDE:
                printf("Token: DIVIDE\n");
                break;
            case ASSIGN:
                printf("Token: ASSIGN\n");
                break;
            case LPAREN:
                printf("Token: LPAREN\n");
                break;
            case RPAREN:
                printf("Token: RPAREN\n");
                break;
            case LBRACKET:
                printf("Token: LBRACKET\n");
                break;
            case RBRACKET:
                printf("Token: RBRACKET\n");
                break;
            case SEMICOLON:
                printf("Token: SEMICOLON\n");
                break;
            case IF:
                printf("Token: IF\n");
                break;
            case THEN:
                printf("Token: THEN\n");
                break;
            case ELSE:
                printf("Token: ELSE\n");
                break;
            case ENDIF:
                printf("Token: ENDIF\n");
                break;
            case WHILE:
                printf("Token: WHILE\n");
                break;
            case DO:
                printf("Token: DO\n");
                break;
            case ENDDO:
                printf("Token: ENDDO\n");
                break;
            case PRINT:
                printf("Token: PRINT\n");
                break;
            default:
                printf("Unknown Token\n");
                break;
        }
    }
    return 0;
}
