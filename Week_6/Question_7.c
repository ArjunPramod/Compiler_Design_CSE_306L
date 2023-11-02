#include <stdio.h>
#include <stdbool.h>

char input[] = "(a,((a,a),(a,a)))";
int position = 0;

bool S();
bool S_prime();
bool L();
bool L_prime();

bool match(char c) {
    if (input[position] == c) {
        position++;
        return true;
    }
    return false;
}

bool S() {
    if (match('(') && L() && match(')') && S_prime()) {
        return true;
    }
    return false;
}

bool S_prime() {
    if (match(';') && L() && S_prime()) {
        return true;
    }
    return true; // S' can also be ε
}

bool L() {
    if (S() && L_prime()) {
        return true;
    }
    return false;
}

bool L_prime() {
    if (match(',') && S() && L_prime()) {
        return true;
    }
    return true; // L' can also be ε
}

int main() {
    bool result = S();
    if (result && input[position] == '\0') {
        printf("String is valid.\n");
    } else {
        printf("String is invalid.\n");
    }
    return 0;
}
