%{
#include <stdio.h>
%}

%%
[aeiouAEIOU]    { printf("Vowel: %s\n", yytext); }
[a-zA-Z]        { printf("Consonant: %s\n", yytext); }
.               { /* Ignore other characters */ }

%%
int main() {
    yylex();
    return 0;
}
