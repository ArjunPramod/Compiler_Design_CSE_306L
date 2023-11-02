%{
#include <stdio.h>
int vowelCount = 0;
int consonantCount = 0;
%}

%%
[aeiouAEIOU]    { vowelCount++; }
[a-zA-Z]        { consonantCount++; }
.               { /* Ignore other characters */ }

%%
int main() {
    yylex();
    printf("Vowels: %d\nConsonants: %d\n", vowelCount, consonantCount);
    return 0;
}
