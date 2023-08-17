// C program that recognizes set of all strings ending with two symbols of same type

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sourceFile, *destinationFile;
    char str[100], f = 'a';
    int i;

    sourceFile = fopen("source.txt", "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    destinationFile = fopen("destination.txt", "w");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }

    fgets(str, 100, sourceFile);

    for (i = 0; str[i] != '\0'; i++) {
        if (f == str[i]) {
            continue;
        }

        f = str[i];
    }

    if (str[i - 1] == f && str[i - 1] == str[i - 2]) {
        fprintf(destinationFile, "String is accepted\n");
    } else {
        fprintf(destinationFile, "String is not accepted\n");
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("Result saved in destination.txt.\n");

    return 0;
}
