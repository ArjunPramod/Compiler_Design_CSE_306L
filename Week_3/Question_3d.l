%{
#include <stdio.h>
%}

%%
.*00$           { printf("String ending with 00: %s\n", yytext); }
.               { /* Ignore other strings */ }

%%
int main() {
    yylex();
    return 0;
}
