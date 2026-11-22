
#include <stdio.h>
#include <string.h>

#define MAX_FILES 20
#define MAX_USERS 10
#define MAX_NAME 50

// Single-level directory
char singleFiles[MAX_FILES][MAX_NAME];
int singleCount = 0;

// Two-level directory
char users[MAX_USERS][MAX_NAME];
char userFiles[MAX_USERS][MAX_FILES][MAX_NAME];
int fileCount[MAX_USERS] = {0};
int userCount = 0;

void singleLevel() {
    int choice;
    char name[MAX_NAME];

    while (1) {
        printf("\n--- SINGLE-LEVEL DIRECTORY ---\n");
        printf("1. Create file\n2. Search file\n3. Delete file\n");
        printf("4. Display files\n5. Back\nChoice: ");
        scanf("%d", &choice);

        if (choice == 5) return;

        if (choice == 1) {
            printf("Enter filename: ");
            scanf("%49s", name);

            if (singleCount == MAX_FILES) {
                printf("Directory is full.\n");
                continue;
            }

            int found = 0;
            for (int i = 0; i < singleCount; i++)
                if (strcmp(singleFiles[i], name) == 0)
                    found = 1;

            if (found)
                printf("File already exists.\n");
            else {
                strcpy(singleFiles[singleCount++], name);
                printf("File created successfully.\n");
            }
        }
        else if (choice == 2) {
            printf("Enter filename: ");
            scanf("%49s", name);

            int found = 0;
            for (int i = 0; i < singleCount; i++)
                if (strcmp(singleFiles[i], name) == 0)
                    found = 1;

            printf(found ? "File found.\n" : "File not found.\n");
        }
        else if (choice == 3) {
            printf("Enter filename: ");
            scanf("%49s", name);

            int i;
            for (i = 0; i < singleCount; i++)
                if (strcmp(singleFiles[i], name) == 0)
                    break;

            if (i == singleCount)
                printf("File not found.\n");
            else {
                for (int j = i; j < singleCount - 1; j++)
                    strcpy(singleFiles[j], singleFiles[j + 1]);
                singleCount--;
                printf("File deleted successfully.\n");
            }
        }
        else if (choice == 4) {
            printf("\nFiles in single-level directory:\n");
            if (singleCount == 0)
                printf("Directory is empty.\n");
            for (int i = 0; i < singleCount; i++)
                printf("%s\n", singleFiles[i]);
        }
        else {
            printf("Invalid choice.\n");
        }
    }
}

int findUser(char name[]) {
    for (int i = 0; i < userCount; i++)
        if (strcmp(users[i], name) == 0)
            return i;
    return -1;
}

void twoLevel() {
    int choice;
    char username[MAX_NAME], filename[MAX_NAME];

    while (1) {
        printf("\n--- TWO-LEVEL DIRECTORY ---\n");
        printf("1. Create user directory\n2. Create file\n");
        printf("3. Search file\n4. Delete file\n");
        printf("5. Display directories\n6. Back\nChoice: ");
        scanf("%d", &choice);

        if (choice == 6) return;

        if (choice == 1) {
            printf("Enter username: ");
            scanf("%49s", username);

            if (findUser(username) != -1)
                printf("User directory already exists.\n");
            else if (userCount == MAX_USERS)
                printf("Maximum users reached.\n");
            else {
                strcpy(users[userCount], username);
                fileCount[userCount] = 0;
                userCount++;
                printf("User directory created.\n");
            }
        }
        else if (choice >= 2 && choice <= 4) {
            printf("Enter username: ");
            scanf("%49s", username);

            int u = findUser(username);
            if (u == -1) {
                printf("User directory not found.\n");
                continue;
            }

            printf("Enter filename: ");
            scanf("%49s", filename);

            int i;
            for (i = 0; i < fileCount[u]; i++)
                if (strcmp(userFiles[u][i], filename) == 0)
                    break;

            if (choice == 2) {
                if (i < fileCount[u])
                    printf("File already exists for this user.\n");
                else if (fileCount[u] == MAX_FILES)
                    printf("User directory is full.\n");
                else {
                    strcpy(userFiles[u][fileCount[u]++], filename);
                    printf("File created successfully.\n");
                }
            }
            else if (choice == 3) {
                printf(i < fileCount[u] ?
                       "File found.\n" : "File not found.\n");
            }
            else {
                if (i == fileCount[u])
                    printf("File not found.\n");
                else {
                    for (int j = i; j < fileCount[u] - 1; j++)
                        strcpy(userFiles[u][j], userFiles[u][j + 1]);
                    fileCount[u]--;
                    printf("File deleted successfully.\n");
                }
            }
        }
        else if (choice == 5) {
            printf("\nTwo-level directory structure:\n");
            for (int i = 0; i < userCount; i++) {
                printf("%s/\n", users[i]);
                for (int j = 0; j < fileCount[i]; j++)
                    printf("  %s\n", userFiles[i][j]);
            }
            if (userCount == 0)
                printf("No user directories created.\n");
        }
        else {
            printf("Invalid choice.\n");
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== DIRECTORY ORGANIZATION =====\n");
        printf("1. Single-level directory\n");
        printf("2. Two-level directory\n");
        printf("3. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1)
            singleLevel();
        else if (choice == 2)
            twoLevel();
        else if (choice == 3) {
            printf("Program terminated.\n");
            break;
        }
        else
            printf("Invalid choice.\n");
    }

    return 0;
}
