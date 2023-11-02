#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODUCTIONS 100
#define MAX_SYMBOLS 10

typedef struct {
    char nonTerminal;
    char production[MAX_SYMBOLS];
} Production;

Production productions[MAX_PRODUCTIONS];
int numProductions;

typedef struct {
    char symbol;
    char firstSet[MAX_SYMBOLS];
    char followSet[MAX_SYMBOLS];
} NonTerminal;

NonTerminal nonTerminals[MAX_SYMBOLS];
int numNonTerminals;

void addToSet(char* set, char symbol) {
    if (strchr(set, symbol) == NULL) {
        int len = strlen(set);
        set[len] = symbol;
        set[len + 1] = '\0';
    }
}

void computeFirstSets() {
    bool changed = true;
    
    while (changed) {
        changed = false;
        
        for (int i = 0; i < numProductions; i++) {
            char A = productions[i].nonTerminal;
            char* alpha = productions[i].production;

            int len = strlen(alpha);

            for (int j = 0; j < len; j++) {
                char X = alpha[j];
                if (X >= 'A' && X <= 'Z') {
                    int beforeLen = strlen(nonTerminals[X - 'A'].firstSet);
                    
                    for (int k = 0; k < beforeLen; k++) {
                        addToSet(nonTerminals[A - 'A'].firstSet, nonTerminals[X - 'A'].firstSet[k]);
                    }

                    if (strchr(nonTerminals[X - 'A'].firstSet, 'E') == NULL) {
                        break;
                    }

                    if (j == len - 1 && strchr(nonTerminals[A - 'A'].firstSet, 'E') == NULL) {
                        addToSet(nonTerminals[A - 'A'].firstSet, 'E');
                    }

                    if (j == len - 1) {
                        int followLen = strlen(nonTerminals[A - 'A'].followSet);
                        
                        for (int k = 0; k < followLen; k++) {
                            addToSet(nonTerminals[X - 'A'].followSet, nonTerminals[A - 'A'].followSet[k]);
                        }
                    }
                } else {
                    addToSet(nonTerminals[A - 'A'].firstSet, X);
                    break;
                }
            }
        }
    }
}

void computeFollowSets() {
    bool changed = true;
    
    while (changed) {
        changed = false;
        
        for (int i = 0; i < numProductions; i++) {
            char A = productions[i].nonTerminal;
            char* alpha = productions[i].production;
            int len = strlen(alpha);
            
            for (int j = len - 1; j >= 0; j--) {
                char B = alpha[j];
                if (B >= 'A' && B <= 'Z') {
                    int beforeLen = strlen(nonTerminals[B - 'A'].followSet);
                    
                    for (int k = 0; k < beforeLen; k++) {
                        addToSet(nonTerminals[B - 'A'].followSet, nonTerminals[A - 'A'].followSet[k]);
                    }
                    
                    if (j == len - 1) {
                        int followLen = strlen(nonTerminals[A - 'A'].followSet);
                        
                        for (int k = 0; k < followLen; k++) {
                            addToSet(nonTerminals[B - 'A'].followSet, nonTerminals[A - 'A'].followSet[k]);
                        }
                    }
                    
                    if (strchr(nonTerminals[B - 'A'].firstSet, 'E') == NULL) {
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    // Initialize your grammar, read the CFG from input, and populate the data structures.
    numNonTerminals = 3;
    nonTerminals[0].symbol = 'A';
    nonTerminals[1].symbol = 'B';
    nonTerminals[2].symbol = 'S';
    
    numProductions = 5;
    productions[0].nonTerminal = 'S';
    strcpy(productions[0].production, "AB");
    productions[1].nonTerminal = 'A';
    strcpy(productions[1].production, "aAE");
    productions[2].nonTerminal = 'B';
    strcpy(productions[2].production, "bBE");
    productions[3].nonTerminal = 'A';
    strcpy(productions[3].production, "E");
    productions[4].nonTerminal = 'B';
    strcpy(productions[4].production, "E");
    
    // Initialize FIRST and FOLLOW sets to empty
    for (int i = 0; i < numNonTerminals; i++) {
        nonTerminals[i].firstSet[0] = '\0';
        nonTerminals[i].followSet[0] = '\0';
    }
    
    // Call computeFirstSets to compute FIRST sets
    computeFirstSets();
    
    // Call computeFollowSets to compute FOLLOW sets
    nonTerminals[2].followSet[0] = '$';  // Follow(S) = {$}
    computeFollowSets();
    
    // Print the computed FIRST and FOLLOW sets
    printf("FIRST sets:\n");
    for (int i = 0; i < numNonTerminals; i++) {
        printf("FIRST(%c) = {%s}\n", nonTerminals[i].symbol, nonTerminals[i].firstSet);
    }
    
    printf("FOLLOW sets:\n");
    for (int i = 0; i < numNonTerminals; i++) {
        printf("FOLLOW(%c) = {%s}\n", nonTerminals[i].symbol, nonTerminals[i].followSet);
    }
    
    return 0;
}
