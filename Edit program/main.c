#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_TEXT_LENGTH 1024

void deleteFile(char *filename) {
    if (remove(filename) == 0) {
        printf("%s file deleted:\n", filename);
    } else {
        perror("Could not delete the file");
    }
}

void displayFileContents(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open the file '%s'\n", filename);
        return;
    }

    char line[MAX_TEXT_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void editFileContents(char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Could not open the file '%s'\n", filename);
        return;
    }

    char newContents[MAX_TEXT_LENGTH];
    printf("Enter the new text (terminate with Ctrl+D in Unix or Ctrl+Z in Windows):\n");

    while (fgets(newContents, sizeof(newContents), stdin) != NULL) {
        size_t len = strlen(newContents);
        if (len > 0 && newContents[len - 1] == '\n') {
            newContents[len - 1] = '\0';
        }
        fprintf(file, "%s\n", newContents);
    }

    fclose(file);
}

int createNewFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        printf("The file already exists\n");
        fclose(file);
        return 0; // exit createFile
    } else {
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Could not create the file '%s'\n", filename);
            return 1; // exit createFile
        }
        fclose(file);
    }
    editFileContents(filename);
    return 2;
}

int main() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the filename to work on\n");
    scanf("%s", filename);

    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Display file\n");
        printf("2. Edit file\n");
        printf("3. Create file\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayFileContents(filename);
                break;
            case 2:
                editFileContents(filename);
                break;
            case 3:
                createNewFile(filename);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;  // exit main
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
