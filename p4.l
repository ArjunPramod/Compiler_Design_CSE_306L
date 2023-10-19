%{
#include <stdio.h>
%}

%%
[0-9]+            { printf("NUMBER\n"); }
[+]               { printf("PLUS\n"); }
[*]               { printf("TIMES\n"); }
[(]               { printf("LPAREN\n"); }
[)]               { printf("RPAREN\n"); }
[\n]              { printf("END\n"); }
[ \t]             ;  // Skip whitespace
.                 { printf("Invalid character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}