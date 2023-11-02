%{
#include <stdio.h>
%}

%%
.*000.*         { printf("String with three consecutive 0's: %s\n", yytext); }
.               { /* Ignore other strings */ }

%%
int main() {
    yylex();
    return 0;
}
