// DFA to accept even number of zero's and one's

#include <stdio.h>
#include <stdlib.h>
#define max 100

int main() {
    FILE *sourceFile, *destinationFile;
    char str[max], f = 'a';
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

    fscanf(sourceFile, "%s", str);

    for (i = 0; str[i] != '\0'; i++) {
        switch (f) {
            case 'a':
                if (str[i] == '0')
                    f = 'b';
                else if (str[i] == '1')
                    f = 'a';
                break;

            case 'b':
                if (str[i] == '0')
                    f = 'a';
                else if (str[i] == '1')
                    f = 'b';
                break;
        }
    }

    if (f == 'a')
        fprintf(destinationFile, "String is accepted\n");
    else
        fprintf(destinationFile, "String is not accepted\n");

    fclose(sourceFile);
    fclose(destinationFile);

    printf("Result saved in destination_file.txt.\n");

    return 0;
}
