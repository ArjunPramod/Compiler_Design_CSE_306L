%{
#include <stdio.h>
int lineCount = 0;
%}

%%
\n              { lineCount++; }
.               { /* Ignore other characters */ }

%%
int main() {
    yylex();
    printf("Lines: %d\n", lineCount);
    return 0;
}
