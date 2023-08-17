// C program to copy the contents from one file to another

#include <stdio.h>

int main() {
    FILE *sourceFile, *destinationFile;
    char ch;

    sourceFile = fopen("source_file.txt", "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    destinationFile = fopen("destination_file.txt", "w");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }

    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully.\n");

    return 0;
}
