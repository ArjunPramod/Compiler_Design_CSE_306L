%{
#include <stdio.h>
%}

%%
[\t ]+          ; 
[\n]            ; 
"//"(.|\n)*     ; 
"/*"([^*]|\n)*"*"+([^/*][^*]|\n)*"*"+"/" ; 

"if"            { printf("IF\n"); }
"then"          { printf("THEN\n"); }
"else"          { printf("ELSE\n"); }
"endif"         { printf("ENDIF\n"); }
"int"           { printf("INT\n"); }
"print"         { printf("PRINT\n"); }
[-+]?[0-9]+     { printf("NUM: %s\n", yytext); }
[a-zA-Z_]\w*    { printf("ID: %s\n", yytext); }
[(){}\[\];,]    { printf("PUNCT: %s\n", yytext); }
.               ; // Ignore any other characters

%%
int main() {
    yylex();
    return 0;
}