/*
Implement lexical analyzer using C for recognizing the following tokens:
- A minimum of 10 keywords of your choice
- Identifiers with the regular expression : letter(letter | digit)*
- Integers with the regular expression: digit+
- Relational operators: <,>,<=,>=,==,!=
- Storing identifiers in symbol table.
- Using files for input and output.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 100

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char cur_char;
    while ((cur_char = fgetc(inputFile)) != EOF) {
        if (cur_char == '(' || cur_char == ')') {
            fprintf(outputFile, "Punctuation: %c\n", cur_char);
        } else if (cur_char == ':') {
            char next_char = fgetc(inputFile);
            if (next_char == '=') {
                fprintf(outputFile, "Assign\n");
            } else {
                fprintf(outputFile, "Error: Invalid token\n");
            }
        } else if (isdigit(cur_char)) {
            // Recognize integers
            int value = cur_char - '0';
            char next_char;
            while (isdigit(next_char = fgetc(inputFile))) {
                value = value * 10 + (next_char - '0');
            }
            ungetc(next_char, inputFile);
            fprintf(outputFile, "Integer: %d\n", value);
        } else if (cur_char == '<' || cur_char == '>' || cur_char == '=') {
            char next_char = fgetc(inputFile);
            if (next_char == '=') {
                fprintf(outputFile, "Relational Operator: %c=\n", cur_char);
            } else {
                ungetc(next_char, inputFile);
                fprintf(outputFile, "Relational Operator: %c\n", cur_char);
            }
        } else if (cur_char == '!') {
            char next_char = fgetc(inputFile);
            if (next_char == '=') {
                fprintf(outputFile, "Relational Operator: !=\n");
            } else {
                fprintf(outputFile, "Error: Invalid token\n");
            }
        } else if (cur_char == '/') {
            char next_char = fgetc(inputFile);
            if (next_char == '/') {
                while ((next_char = fgetc(inputFile)) != '\n') {
                    // Skip the comment
                }
            } else if (next_char == '*') {
                int commentEnded = 0;
                char prev_char = ' ';
                while (!commentEnded && (next_char = fgetc(inputFile)) != EOF) {
                    if (prev_char == '*' && next_char == '/') {
                        commentEnded = 1;
                    }
                    prev_char = next_char;
                }
            } else {
                ungetc(next_char, inputFile);
                fprintf(outputFile, "Divide Operator: /\n");
            }
        } else if (isalpha(cur_char) || cur_char == '_') {
            // Recognize identifiers and keywords
            char identifier[MAX_IDENTIFIER_LENGTH];
            int i = 0;
            identifier[i++] = cur_char;
            while (isalnum(cur_char = fgetc(inputFile)) || cur_char == '_') {
                identifier[i++] = cur_char;
            }
            identifier[i] = '\0';
            ungetc(cur_char, inputFile);

            fprintf(outputFile, "Identifier: %s\n", identifier);
        } else if (cur_char == '+' || cur_char == '-') {
            // Recognize arithmetic operators
            fprintf(outputFile, "Arithmetic Operator: %c\n", cur_char);
        } else if (cur_char == '\n' || cur_char == ' ' || cur_char == '\t') {
            // Skip whitespace characters
        } else {
            fprintf(outputFile, "Error: Invalid token\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Lexical analysis completed. Check output.txt for results.\n");

    return 0;
}
