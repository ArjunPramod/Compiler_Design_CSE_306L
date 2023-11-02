#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *input;
int index = 0;
int error = 0;

void E();
void E_prime();
void T();
void T_prime();
void F();

void match(char expected) {
    if (input[index] == expected) {
        index++;
    } else {
        printf("Error: Expected %c but found %c\n", expected, input[index]);
        error = 1;
    }
}

void E() {
    T();
    E_prime();
}

void E_prime() {
    if (input[index] == '+') {
        match('+');
        T();
        E_prime();
    }
    // E' -> ε (empty string), do nothing
}

void T() {
    F();
    T_prime();
}

void T_prime() {
    if (input[index] == '*') {
        match('*');
        F();
        T_prime();
    }
    // T' -> ε (empty string), do nothing
}

void F() {
    if (input[index] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalpha(input[index])) {
        match(input[index]);
    } else {
        printf("Error: Invalid character %c\n", input[index]);
        error = 1;
    }
}

int main() {
    input = "(a+b)*c";
    E();

    if (input[index] == '\0' && !error) {
        printf("Parsing successful.\n");
    } else {
        printf("Parsing failed.\n");
    }

    return 0;
}
